#include "ui.h"
#include "i2c.h"
#include "cache.h"
#include "qff.h"
#include "utils.h"
#include "fmt.h"
#include "console.h"
#include "fb.h"

uint8_t *top_screen_fb[2];
uint8_t *bottom_screen_fb[2];
uint8_t *top_screen;
uint8_t *bottom_screen;

bool current_fb = false;

void main(int argc, char** argv) {
  if (argc >= 2) {
    uint8_t **fb = (uint8_t **)(void *)argv[1];
    top_screen_fb[0] = fb[0];
    top_screen_fb[1] = fb[1];
    bottom_screen_fb[0] = fb[2];
    bottom_screen_fb[1] = fb[3];
    top_screen = top_screen_fb[0];
    bottom_screen = bottom_screen_fb[0];
  } else {
    top_screen_fb[0] = (uint8_t *)(*(uint32_t *)0x23FFFE00);
    top_screen_fb[1] = (uint8_t *)(*(uint32_t *)0x23FFFE04);
    bottom_screen_fb[0] = (uint8_t *)(*(uint32_t *)0x23FFFE08);
    bottom_screen_fb[1] = (uint8_t *)(*(uint32_t *)0x23FFFE0C);
    top_screen = top_screen_fb[0];
    bottom_screen = bottom_screen_fb[0];
  }

  console_t console = {top_screen_fb[0], {}, 0};

  ClearScreenF(true, true, COLOR_STD_BG);
  
  console_puts(&console, "lunix v0.1.0\n");
  while (true) {  
    uint16_t events = system_events();

    console_puts(&console, "events: ");
    char buf[32];
    snprintf(buf, sizeof(buf), "events: %u\n", events);
    console_puts(&console, buf);   
    console_puts(&console, "\n");
    
    if (!(system_shellstate() & 2) || system_events() & 1) {
      break;
    }

    current_fb = !current_fb;
    top_screen = top_screen_fb[current_fb];
    bottom_screen = bottom_screen_fb[current_fb];
    console.screen = top_screen;

    ClearScreenF(true, true, COLOR_STD_BG);
    console_draw(&console);
    
    // TODO: implement/fix vblank
    flushEntireDCache();
    // fb_swap(current_fb);
    system_wait(1000 / 20);
  }

  fs_deinit();
  ClearScreenF(true, true, COLOR_STD_BG);
  
  system_poweroff();
}
