#include <stdint.h>
#include "arm11.h"

volatile uint32_t *operation = (volatile uint32_t *)0x1FF80004;
volatile uint32_t *parameter = (volatile uint32_t *)0x1FF80008;

void arm11_main() {
  *operation = ARM11_READY;
  *parameter = 0;
  for (;;) {
    if (*operation == ARM11_SET_BRIGHT) {
      *((volatile uint32_t *)(0x10202240)) = *parameter;
      *operation = ARM11_READY;
    }
  }
}
