#pragma once
#include "kernel/lib/fmt.h"
#include "kernel/fs.h"
#include "kernel/console.h"
#include "fatfs/qff.h"
#include "common/common.h"

void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

size_t strlen(const char *s);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);

char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);

char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);

char *strstr(const char *haystack, const char *needle);

// not added (snprintf and vsnprintf)
int snprintf(char *str, size_t size, const char *format, ...);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);

int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);

int printf(const char *format, ...);
