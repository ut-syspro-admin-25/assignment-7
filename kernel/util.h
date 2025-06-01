#pragma once
#include "kernel.h"

void *memset(void *dst, int c, uint64_t n);
void *memcpy(void *dst, const void *src, uint64_t n);
void *memmove(void *dst, const void *src, uint64_t n);
char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, int len);
