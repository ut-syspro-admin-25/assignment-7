#pragma once
unsigned int measure_lapic_freq_khz();
void lapic_periodic_exec(unsigned int msec, void (*callback)(unsigned long long));
void lapic_intr_handler_internal();
