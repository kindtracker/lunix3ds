#include "fatfs/ff.h"
#include "kernel/fs.h"

FILE *fopen(const char *file_name, const char *mode) {
/*  BYTE flags = 0;

  if (strcmp(mode, "r") == 0) {
     flags = FA_READ | FA_OPEN_EXISTING;
  } else if (strcmp(mode, "r+") == 0) {
    flags = FA_READ | FA_WRITE | FA_OPEN_EXISTING;
  } else if (strcmp(mode, "w") == 0) {
    flags = FA_WRITE | FA_CREATE_ALWAYS;
  } else if (strcmp(mode, "w+") == 0) {
    flags = FA_READ | FA_WRITE | FA_CREATE_ALWAYS;
  } else if (strcmp(mode, "a") == 0) {
    flags = FA_WRITE | FA_OPEN_ALWAYS;
  } else if (strcmp(mode, "a+") == 0) {
    flags = FA_READ | FA_WRITE | FA_OPEN_ALWAYS;
  } else {
    return FR_INVALID_PARAMETER;
  }
 
  if (mode[0] == 'a') {
    res = f_lseek(fp, f_size(fp));
  }*/
}
