#include "kernel.h"
#include "ioapic.h"

struct IOAPIC
{
        uint32_t reg;
        uint32_t pad[3];
        uint32_t data;
};

volatile struct IOAPIC *ioapic = (volatile struct IOAPIC *)0xfec00000;

#define REG_ID     0x00  // Register index: ID
#define REG_VER    0x01  // Register index: version
#define REG_TABLE  0x10  // Redirection table base

static void ioapic_w(unsigned int reg, unsigned int data)
{
        ioapic->reg = reg;
        ioapic->data = data;
}

void ioapic_enable(int irq)
{
        int off = irq - 32;

        ioapic_w(REG_TABLE+2*off, irq);
        ioapic_w(REG_TABLE+2*off+1, 0 << 24);
}
