#include "kernel/fb.h"
#include "kernel/arm11.h"
#include "common/common.h"

void fb_swap(bool is_alt) {
  kernel_invoke_arm11_function(ARM11_SWAP, is_alt);
}

void fb_wait_vblank(bool is_top) {
  uint32_t op = is_top ? ARM11_GET_STATUS_TOP : ARM11_GET_STATUS_BOT;
  while (!(kernel_invoke_arm11_function_return(op, 0) & (1u << 17)));
}
