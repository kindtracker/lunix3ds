#include "i2c.h"
#include "cache.h"

void system_start_chrono();
uint64_t system_chrono();
void system_reboot();
void system_poweroff();
uint8_t system_shellstate();
void system_wait(u64 ms);
void system_wait_vblank(u64 ms);
uint16_t system_events();
