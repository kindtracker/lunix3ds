#pragma once
#include <stdint.h>
#define ARM11_READY  0
#define ARM11_SWAP   1

void kernel_invoke_arm11_function(uint32_t op, uint32_t param);
