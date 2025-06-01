#include "kernel.h"
#include "segmentation.h"

struct GDTR {
        unsigned short limit;
        unsigned long long base;
} __attribute((packed));

struct GdtDesc {
        uint16_t limit_15_0;
        uint16_t base_15_0;
        uint8_t  base_23_16;
        uint8_t  type : 4;
        uint8_t  s : 1;         
        uint8_t  dpl : 2;       
        uint8_t  p : 1;         
        uint8_t  lim_19_16 : 4;
        uint8_t  avl : 1; 
        uint8_t  l : 1; 
        uint8_t  db : 1; 
        uint8_t  g : 1; 
        uint8_t  base_31_24;
} __attribute__((packed));

struct TSSDesc {
        uint16_t limit_15_0;
        uint16_t base_15_0;
        uint8_t  base_23_16;
        uint8_t  type : 4;
        uint8_t  s : 1;         
        uint8_t  dpl : 2;       
        uint8_t  p : 1;         
        uint8_t  lim_19_16 : 4;
        uint8_t  avl : 1; 
        uint8_t  l : 1; 
        uint8_t  db : 1; 
        uint8_t  g : 1; 
        uint8_t  base_31_24;
        uint32_t base_63_32;
        uint32_t reserved;
} __attribute__((packed));

static void setseg(uint64_t *gdt, int type, uint32_t base, uint32_t limit, int dpl)
{
        struct GdtDesc *desc = (struct GdtDesc *)gdt;

        desc->limit_15_0 = (limit >> 12) & 0xffff;
        desc->base_15_0 = base & 0xffff;
        desc->base_23_16 = (base >> 16) & 0xff;
        desc->type = type;
        desc->s = 1;
        desc->dpl = dpl;
        desc->p = 1;
        desc->lim_19_16 = (limit >> 28) & 0xf;
        desc->avl = 0;
        desc->l = 1;
        desc->db = 0;
        desc->g = 1;
        desc->base_31_24 = (base >> 24) & 0xff;
}

static void settssseg(uint64_t *gdt, int type, uint64_t base, uint32_t limit, int dpl)
{
        struct TSSDesc *desc = (struct TSSDesc *)gdt;

        desc->limit_15_0 = limit & 0xffff;
        desc->base_15_0 = base & 0xffff;
        desc->base_23_16 = (base >> 16) & 0xff;
        desc->type = type;
        desc->s = 0;
        desc->dpl = dpl;
        desc->p = 1;
        desc->lim_19_16 = (limit >> 16) & 0xf;
        desc->avl = 0;
        desc->l = 0;
        desc->db = 0;
        desc->g = 0;
        desc->base_31_24 = (base >> 24) & 0xff;
        desc->base_63_32 = base >> 32;
        desc->reserved = 0;
}

struct TSS tss = {0};

unsigned long long GDT[NR_SEG];
//unsigned long long GDT[] = {
//  0x0000000000000000, /* NULL descriptor */
//  0x00af9a000000ffff, /* base=0, limit=4GB, mode=code(r-x),kernel */
//  0x00cf93000000ffff, /* base=0, limit=4GB, mode=data(rw-),kernel */
//};

void ltr(unsigned short sel)
{
        asm volatile ("ltr %0" :: "r" (sel));
}

void init_tss(void)
{
        settssseg(GDT + SEG_TSS, STA_TSSA, (uint64_t)&tss, sizeof(tss) - 1, DPL_KERNEL);
}

void init_segmentation() {
        struct GDTR gdtr;

        GDT[SEG_NULL] = 0;     // NULL Descriptor
        setseg(GDT + SEG_KCODE, STA_X|STA_R, 0, 0xffffffff, DPL_KERNEL);
        setseg(GDT + SEG_KDATA, STA_W, 0, 0xffffffff, DPL_KERNEL);
        setseg(GDT + SEG_UCODE, STA_X|STA_R, 0, 0xffffffff, DPL_USER);
        setseg(GDT + SEG_UDATA, STA_W, 0, 0xffffffff, DPL_USER);

        init_tss();

        gdtr.limit = sizeof(GDT);
        gdtr.base = (unsigned long long)GDT;
        load_gdt((unsigned long long)&gdtr);
        ltr(SEG_TSS << 3);
}
