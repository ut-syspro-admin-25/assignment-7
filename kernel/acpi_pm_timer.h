#pragma once

#include "hardware.h"

void init_acpi_pm_timer(struct RSDP *rsdp);
void pm_timer_sleep(unsigned int ms);
