#include "fb.h"
#include "common.h"
#include "arm11.h"

void fb_swap(bool is_alt) {
  kernel_invoke_arm11_function(ARM11_SWAP, is_alt);
}
