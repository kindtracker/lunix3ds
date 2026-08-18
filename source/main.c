#include "ui.h"
#include "i2c.h"
#include "cache.h"
#include "qff.h"
#include "utils.h"
#include "fmt.h"
#include "console.h"

uint8_t *top_screen, *bottom_screen;

void main(int argc, char** argv) {
  if (argc >= 2) {
    uint8_t **fb = (uint8_t **)(void *)argv[1];
    top_screen = fb[0];
    bottom_screen = fb[2];
  } else {
    top_screen = (uint8_t *)(*(uint32_t *)0x23FFFE00);
    bottom_screen = (uint8_t *)(*(uint32_t *)0x23FFFE08);
  }

  console_t console = {top_screen, {}, 0};

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

    ClearScreenF(true, true, COLOR_STD_BG);
    console_draw(&console);
    
    // TODO: implement/fix vblank
    system_wait(1000/60);
  }

  fs_deinit();
  ClearScreenF(true, true, COLOR_STD_BG);
  
  system_poweroff();
}
