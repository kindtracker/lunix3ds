#include "hardware/i2c.h"
#include "hardware/cache.h"
#include "hardware/system.h"
#include "ui/ui.h"
#include "fatfs/qff.h"
#include "utils/fmt.h"
#include "kernel/console.h"
#include "kernel/fb.h"
#include "kernel/boot.h"

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

  booting = 0;
  boot();
  console.screen = top_screen_fb[0];

  ClearScreenF(true, true, COLOR_STD_BG);
  
  while (true) {  
    if ((!(system_shellstate() & 2)) || system_special_keys()) {
      break;
    }

    current_fb = !current_fb;
    top_screen = top_screen_fb[current_fb];
    bottom_screen = bottom_screen_fb[current_fb];
    console.screen = top_screen;

    if (console.new) {
      ClearScreenF(true, true, COLOR_STD_BG);
      console_draw(&console);
      console.new = false;
    }
    boot();
   
    // TODO: implement/fix vblank, framebuffer swaping
  }

  fs_deinit();
  ClearScreenF(true, true, COLOR_STD_BG);
  
  system_poweroff();
}
