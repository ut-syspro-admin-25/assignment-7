#include "kernel.h"
#include "interrupt.h"
#include "lapic_timer.h"
#include "segmentation.h"
#include "process.h"
#include "console.h"
#include "ioapic.h"

enum Gatetype {
        GATETYPE_64_INTR = 0xe,
        GATETYPE_64_TRAP = 0xf,
};

struct InterruptDescriptor {
        uint16_t offset_0_15;
        uint16_t sel;
        uint8_t  ist: 3;
        uint8_t  _rsrv0: 5;
        uint8_t  gatetype: 4;
        uint8_t  _zero: 1;
        uint8_t  dpl: 2;
        uint8_t  p: 1;
        uint16_t offset_16_31;
        uint32_t offset_32_63;
        uint32_t _rsrv1;
} __attribute__((packed));

struct InterruptDescriptor IDT[256];

void lapic_intr_handler();
void fault_handler();
void syscall_handler();

static void load_idt_to_idtr(struct InterruptDescriptor *idt, unsigned long idtsize) {
        uint16_t t[5];

        t[0] = (uint16_t)idtsize - 1;
        t[1] = (uint16_t)(uint64_t)idt;
        t[2] = (uint16_t)((uint64_t)idt >> 16);
        t[3] = (uint16_t)((uint64_t)idt >> 32);
        t[4] = (uint16_t)((uint64_t)idt >> 48);

        asm volatile ("lidt (%0)" :: "r"(t));
}

static inline void set_interrupt_handler(struct InterruptDescriptor *desc, uint64_t offset, uint16_t sel,
                                         enum Gatetype gatetype, uint8_t dpl)
{
        desc->offset_0_15   = (uint16_t)offset;
        desc->sel           = sel;
        desc->ist           = 0;
        desc->_rsrv0        = 0;
        desc->gatetype      = gatetype;
        desc->_zero         = 0;
        desc->dpl           = dpl;
        desc->p             = 1;
        desc->offset_16_31  = (uint16_t)(offset >> 16);
        desc->offset_32_63  = (uint32_t)(offset >> 32);
        desc->_rsrv1        = 0;
}

void fault_handler_internal(unsigned long long sp)
{
        for (;;)
                ;
}

void init_intr() {
        // Get segment register value
        unsigned short cs = SEG_KCODE << 3;
        // asm volatile ("mov %%cs, %0" : "=r"(cs));

        void* lapic_intr_handler_addr;
        asm volatile ("lea lapic_intr_handler(%%rip), %0" : "=r"(lapic_intr_handler_addr));
        void* syscall_handler_addr;
        asm volatile ("lea syscall_handler(%%rip), %[handler]" : [handler]"=r"(syscall_handler_addr));
        void* keyboard_intr_handler_addr;
        asm volatile ("lea keyboard_intr_handler(%%rip), %[handler]" : [handler]"=r"(keyboard_intr_handler_addr));

        // enable keyboard irq
        ioapic_enable(33);

        // Register PageFault handler
        set_interrupt_handler (IDT + 14, (uint64_t)fault_handler, cs, GATETYPE_64_INTR, 0);

        // Register Local APIC Timer handler
        set_interrupt_handler (IDT + 32, (uint64_t)lapic_intr_handler_addr, cs, GATETYPE_64_INTR, 0);

        // Register Keyboard interrupt handler
        set_interrupt_handler (IDT + 33, (uint64_t)keyboard_intr_handler_addr, cs, GATETYPE_64_INTR, 0);

        // Register Syscall handler
        set_interrupt_handler (IDT + 0x80, (uint64_t)syscall_handler_addr, cs, GATETYPE_64_TRAP, DPL_USER);

        // Tell CPU the location of IDT
        load_idt_to_idtr(IDT, sizeof IDT);

        // Set IF bit in RFLAGS register
        asm volatile ("sti");
}
