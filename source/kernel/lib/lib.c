#include "kernel/lib.h"

char temp_buf[65536];

static void temp_buf_clear() {
  memset(&temp_buf, 0, sizeof(temp_buf));
}

int printf(const char *format, ...) {
  temp_buf_clear();

  va_list args;
  va_start(args, format);
  snprintf(temp_buf, format, args);
  va_end(args);

  console_puts(&console, temp_buf);
}
