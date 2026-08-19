#include <stdint.h>
#include "arm11.h"

#define PDC_TOP_FB_SELECT    (*(volatile uint32_t *)0x10400478)
#define PDC_BOTTOM_FB_SELECT (*(volatile uint32_t *)0x10400578)

volatile uint32_t *operation = (volatile uint32_t *)0x1FF80004;
volatile uint32_t *parameter = (volatile uint32_t *)0x1FF80008;

void arm11_main() {
  *operation = ARM11_READY;
  *parameter = 0;
  for (;;) {
    if (*operation == ARM11_SWAP) {
      uint32_t is_alt = *parameter & 1;

      PDC_TOP_FB_SELECT = is_alt;
      PDC_BOTTOM_FB_SELECT = is_alt;

      *operation = ARM11_READY;
    }
  }
}
