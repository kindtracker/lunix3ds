#include "arm11.h"

volatile uint32_t *operation = (volatile uint32_t *)0x1FF80004;
volatile uint32_t *parameter = (volatile uint32_t *)0x1FF80008;

void kernel_invoke_arm11_function(uint32_t op, uint32_t param) {
  *parameter = param;
  *operation = op;
}
