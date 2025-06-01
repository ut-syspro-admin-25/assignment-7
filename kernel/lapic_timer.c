#include "kernel.h"
#include "lapic_timer.h"
#include "acpi_pm_timer.h"

#define COUNT_MAX 0xffffffff

volatile unsigned int *lvt_timer = (unsigned int *)0xfee00320;
volatile unsigned int *initial_count = (unsigned int *)0xfee00380;
volatile unsigned int *current_count = (unsigned int *)0xfee00390;
volatile unsigned int *divide_config = (unsigned int *)0xfee003e0;

unsigned int lapic_timer_freq = 0;

volatile unsigned int *lapic_eoi = (unsigned int *)0xfee000b0;

void (*reserved_callback)(unsigned long long sp);

// Set End of Interrupt
void eoi(void) {
        *lapic_eoi = 0;
}

void set_measure_lapic_freq() {
        // Set Divide config
        *divide_config = 0xB;   // 1:1
        // Initialize LAPIC One-Shot timer

        // Wait 1000ms
        pm_timer_sleep (1000);

        // Calculate LAPIC Freq.
}

void lapic_periodic_exec(unsigned int msec, void (*callback)(unsigned long long)) {
        if (!lapic_timer_freq) {
                set_measure_lapic_freq();
                if (!lapic_timer_freq) {
                        return;
                }
        }

        reserved_callback = callback;

        // Set LAPIC Periodic Timer
        //
        // Here
        //
}

void lapic_intr_handler_internal(unsigned long long sp) {
        eoi();

        reserved_callback(sp);
}
