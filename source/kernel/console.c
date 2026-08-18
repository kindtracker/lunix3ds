#include "ui.h"
#include "common.h"
#include "console.h"

void console_put(console_t *console, char chr) {
  if (console->buffer_len >= sizeof(console->buffer)) {
    memmove(console->buffer, console->buffer + 1, sizeof(console->buffer) - 1);
    console->buffer_len = sizeof(console->buffer) - 1;
  }
  console->buffer[console->buffer_len++] = chr;
}

void console_puts(console_t *console, const char *str) {
  for (int i = 0; i < (int)strlen(str); i++) {
    console_put(console, str[i]);
  }
}

void console_draw(console_t *console) {
  int lines = 0;
  for (int i = 0; i < console->buffer_len; i++) {
    char chr = console->buffer[i];
    if (chr == '\n') {
      lines++;
    }
  }
  int visible_lines = SCREEN_HEIGHT_TOP / 8;
  int first_line = 0;
  if (lines >= visible_lines) {
    first_line = lines - visible_lines;
  }

  int current_line = 0;
  int x = 0;
  int y = 0;
  for (int i = 0; i < console->buffer_len; i++) {
    char chr = console->buffer[i];
    if (chr == '\n') {
      current_line++;
      if (current_line > first_line) { 
        x = 0;
        y += 8; 
      }
      continue;
    }
    if (current_line < first_line) { 
      continue;
    }

    DrawCharacter(console->screen, chr, x, y, COLOR_STD_FONT, COLOR_STD_BG);
    x += 8;
    if (x + 8 > SCREEN_WIDTH_TOP) {
      x = 0;
      y += 8;
    }
  }
}
