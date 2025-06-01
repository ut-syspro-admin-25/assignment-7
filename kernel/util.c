#include "kernel.h"
#include "util.h"

int strncmp(const char *s1, const char *s2, int len)
{
        while (*s1 && *s1 == *s2 && len > 0) {
                s1++;
                s2++;
                len--;
        }
        if (len == 0)
                return 0;
        return *s1 - *s2;
}

void *memset(void *dst, int c, uint64_t n)
{
        char *d = dst;

        while (n-- > 0)
                *d++ = c;
        return dst;
}

void *memcpy(void *dst, const void *src, uint64_t n)
{
        return memmove (dst, src, n);
}

void *memmove(void *dst, const void *src, uint64_t n)
{
        char *d = dst;
        const char *s = src;

        if (s > d) {
                while (n-- > 0)
                        *d++ = *s++;
        } else {
                d += n;
                s += n;
                while (n-- > 0)
                        *--d = *--s;
        }
        return dst;
}

char *strcpy(char *dst, const char *src)
{
        char *r = dst;

        while ((*dst++ = *src++) != 0)
                ;
        return r;
}

int strcmp(const char *s1, const char *s2)
{
        while (*s1 && *s1 == *s2)
        {
                s1++;
                s2++;
        }
        return *s1 - *s2;
}
