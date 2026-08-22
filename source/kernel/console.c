#include "ui/ui.h"
#include "common/common.h"
#include "kernel/console.h"

void console_put(console_t *console, char chr) {
  if (console->buffer_len >= sizeof(console->buffer)) {
    memmove(console->buffer, console->buffer + 1, sizeof(console->buffer) - 1);
    console->buffer_len = sizeof(console->buffer) - 1;
  }
  console->buffer[console->buffer_len++] = chr;
  console->new = true;
}

void console_puts(console_t *console, const char *str) {
  for (int i = 0; i < (int)strlen(str); i++) {
    console_put(console, str[i]);
  }
}

static void console_scroll(console_t *console) {
  uint8_t *fb = console->screen;

  const int width = SCREEN_WIDTH_TOP;
  const int height = SCREEN_HEIGHT_TOP;
  const int scroll = 8;

  for (int x = 0; x < width; x++) {
    uint8_t *column = fb + x * height * BPP;
    memmove(column + scroll * BPP, column, (height - scroll) * BPP);
    memset(column, 0, scroll * BPP);
  }
}

void console_draw(console_t *console) {
  int lines = 1;
  int x = 0;

  for (int i = 0; i < console->buffer_len; i++) {
    char chr = console->buffer[i];
    if (chr == '\n') {
      lines++;
      x = 0;
      continue;
    }
    if (x + 8 > SCREEN_WIDTH_TOP) {
      lines++;
      x = 0;
    }
    x += 8;
  }
  
  int visible_lines = SCREEN_HEIGHT_TOP / 8;
  if (lines > (visible_lines + console->scroll)) {
    console_scroll(console);
    console->scroll++;
  }

  int current_line = 0;
  int y = 0;
  x = 0;
  for (int i = 0; i < console->buffer_len; i++) {
    char chr = console->buffer[i];
    if (chr == '\n') {
      current_line++;
      x = 0;
      if (current_line >= console->scroll) { 
        y += 8; 
      }
      continue;
    }
    if (current_line < console->scroll) { 
      continue;
    }

    DrawCharacter(console->screen, chr, x, y, COLOR_STD_FONT, COLOR_STD_BG);
    x += 8;
    if (x + 8 > SCREEN_WIDTH_TOP) {
      x = 0;
      y += 8; 
      current_line++;
    }
  }
}
