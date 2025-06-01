#pragma once
void init_segmentation();

/* Task State Segment */
struct TSS {
        uint32_t reserved0;
        uint64_t rsp0;        // Privilege level 0 stack pointer
        uint64_t rsp1;        // Privilege level 1 stack pointer
        uint64_t rsp2;        // Privilege level 2 stack pointer
        uint64_t reserved1;
        uint64_t ist1;        // Interrupt Stack Table entry 1
        uint64_t ist2;        // Interrupt Stack Table entry 2
        uint64_t ist3;        // Interrupt Stack Table entry 3
        uint64_t ist4;        // Interrupt Stack Table entry 4
        uint64_t ist5;        // Interrupt Stack Table entry 5
        uint64_t ist6;        // Interrupt Stack Table entry 6
        uint64_t ist7;        // Interrupt Stack Table entry 7
        uint64_t reserved2;
        uint16_t reserved3;
        uint16_t io_map_base;
} __attribute__((packed));

#define DPL_KERNEL      0x0
#define DPL_USER        0x3

// Application segment type bits
#define STA_X       0x8
#define STA_W       0x2
#define STA_R       0x2

#define STA_TSSA    0x9

#define SEG_NULL        0x0
#define SEG_KCODE       0x1
#define SEG_KDATA       0x2
#define SEG_UCODE       0x3
#define SEG_UDATA       0x4
#define SEG_TSS         0x5
#define NR_SEG          0x7

extern struct TSS tss;

void ltr(unsigned short sel);
void load_gdt(unsigned long long addr);
