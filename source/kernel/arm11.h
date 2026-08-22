#pragma once
#include <stdint.h>

#define ARM11_READY       0
#define ARM11_SET_BRIGHT  1

void kernel_invoke_arm11_function(uint32_t op, uint32_t param);
uint32_t kernel_invoke_arm11_function_return(uint32_t operation, uint32_t param);
