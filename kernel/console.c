#include "kernel.h"
#include "hardware.h"
#include "console.h"
#include "util.h"
#include "keyboard.h"
#include "process.h"

static struct FrameBuffer *FB;
static unsigned int fb_x, fb_y;
extern unsigned char font[128][8];

#define va_list                 __builtin_va_list
#define va_start(_v, _l)        __builtin_va_start (_v, _l)
#define va_arg(_v, _l)          __builtin_va_arg (_v, _l)
#define va_end(_v)              __builtin_va_end (_v)
#define va_copy(_d, _s)         __builtin_va_copy (_d, _s)

static void
putchar (unsigned char c)
{
        ;
}

void
puts (char *s)
{
        ;
}

void
puth (unsigned long long num)
{
}

void init_console(struct FrameBuffer *fb)
{
        FB = fb;

        if (!FB)
                return;

        for (unsigned int i = 0; i < FB->height; i++) {
                for (unsigned int j = 0; j < FB->width; j++) {
                        struct Pixel *pixel = FB->base + FB->width * i + j;
                        pixel->r = 0;
                        pixel->g = 0;
                        pixel->b = 0;
                }
        }

        fb_x = 0;
        fb_y = 0;
}

int console_read(char *buf, int n)
{
        return -1;
}

void console_irq(void)
{
        int c;

        while ((c = keyboard_getchar()) >= 0) {
                switch (c) {
                // BACKSPACE
                case '\x7f':
                case C('H'):    // ctrl-h
                        putchar('\b');    // echoback
                        break;
                default:
                        if (c != 0) {
                                c = (c == '\r') ? '\n' : c;
                                putchar(c);    // echoback
                        }
                        break;
                }
        }
}
