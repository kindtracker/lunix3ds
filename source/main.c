#include "hardware/i2c.h"
#include "hardware/cache.h"
#include "hardware/system.h"
#include "ui/ui.h"
#include "fatfs/qff.h"
#include "kernel/console.h"
#include "kernel/fb.h"
#include "kernel/boot.h"
#include "kernel/lib.h"

uint8_t *top_screen;
uint8_t *bottom_screen;

bool current_fb = false;

// This table is from GodMode9
static const u8 brightness_lvls[] = {
	0x10, 0x17, 0x1E, 0x25,
	0x2C, 0x34, 0x3C, 0x44,
	0x4D, 0x56, 0x60, 0x6B,
	0x79, 0x8C, 0xA7, 0xD2
};

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
  
  while (true) {  
    if ((!(system_shellstate() & 2)) || system_special_keys()) {
      break;
    }

    int bright_lvl = (system_volume_slider() >> 2);
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
