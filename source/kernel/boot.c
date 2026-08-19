#include "boot.h"
#include "qff.h"
#include "console.h"

int booting;
console_t console;

int boot() {
  if (booting == 0) {
    console = (console_t){0, {}, 0, false};
    console_puts(&console, "lunix v0.1.0\n");
    console_puts(&console, "booting\n");
    booting = 1;
  } else if (booting == 1) {
    console_puts(&console, "initializing filesystem\n");
    if (fs_init() != FR_OK) {
      console_puts(&console, "failed to initialize filesystem\n");
      fs_deinit();
      booting = 0;
      return 1;
    } else {
      console_puts(&console, "filesystem is initialized\n");
      booting = 2;
      return 0;
    }
  }
  return 0;
}
