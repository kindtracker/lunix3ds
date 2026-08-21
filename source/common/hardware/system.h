#include "i2c.h"
#include "cache.h"

void system_start_chrono();
uint64_t system_chrono();
void system_reboot();
void system_poweroff();
uint8_t system_shellstate();
void system_wait(u64 ms);
void system_vblank_init();
void system_wait_vblank();
uint32_t system_special_keys();
uint32_t system_volume_slider();
