#include "hardware/i2c.h"
#include "hardware/cache.h"
#include "hardware/system.h"
#include "ui/ui.h"
#include "fatfs/qff.h"
#include "kernel/console.h"
#include "kernel/boot.h"
#include "kernel/lib.h"

uint8_t *top_screen;
uint8_t *bottom_screen;

void main(int argc, char** argv) {
  if (argc >= 2) {
    uint8_t **fb = (uint8_t **)(void *)argv[1];
    top_screen = fb[0];
    bottom_screen = fb[2];
  } else {
    top_screen = (uint8_t *)(*(uint32_t *)0x23FFFE00);
    bottom_screen = (uint8_t *)(*(uint32_t *)0x23FFFE08);
  }

  booting = 0;
  boot();
  console.screen = top_screen;

  ClearScreenF(true, true, COLOR_STD_BG);
  
  int old_bright_lvl = 0;
  while (true) {  
    if ((!(system_shellstate() & 2)) || system_special_keys()) {
      break;
    }

    int bright_lvl = system_volume_slider() << 2;
    if (old_bright_lvl != bright_lvl) {
      if (bright_lvl == 256) bright_lvl = 255;
      if (bright_lvl == 0) bright_lvl = 16;
      kernel_invoke_arm11_function(ARM11_SET_BRIGHT, bright_lvl);
      old_bright_lvl = bright_lvl;
    }
    printf("bright_lvl: %d\n", bright_lvl);
    
    if (console.new) {
      console_draw(&console);
      console.new = false;
    }
    boot();

    system_wait(1000 / 30);
  }

  fs_deinit();
  ClearScreenF(true, true, COLOR_STD_BG);
  
  system_poweroff();
}
