#pragma once

#include "hardware.h"

void puts (char *s);
void init_console (struct FrameBuffer *fb);
void puth (unsigned long long num);
int printf (const char *fmt, ...);
void console_irq(void);
int console_read(char *buf, int n);
