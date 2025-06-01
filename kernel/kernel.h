#ifndef _KERNEL_H
#define _KERNEL_H

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-variable"

typedef unsigned char           uint8_t;
typedef signed char             int8_t;
typedef unsigned short          uint16_t;
typedef signed short            int16_t;
typedef unsigned int            uint32_t;
typedef signed int              int32_t;
typedef unsigned long long      uint64_t;
typedef signed long long        int64_t;

typedef _Bool   bool;

#define false   (0)
#define true    (1) 

#define NULL    ((void *)0)

static inline uint8_t inb(uint16_t port)
{
        uint8_t data;
        asm volatile ("inb %1, %0" : "=a"(data) : "d"(port));
        return data;
}

static inline uint32_t inl(uint16_t port)
{
        uint32_t data;
        asm volatile ("inl %1, %0" : "=a"(data) : "d"(port));
        return data;
}

#endif  // _KERNEL_H
