#include "kernel.h"
#include "hardware.h"
#include "segmentation.h"
#include "interrupt.h"
#include "memory.h"
#include "console.h"
#include "lapic_timer.h"
#include "acpi_pm_timer.h"
#include "page_allocator.h"
#include "ramdisk.h"
#include "fs.h"
#include "process.h"

void start(void *SystemTable __attribute__ ((unused)), struct HardwareInfo *_hardware_info, unsigned long long kernel_param_dummy) {
        // From here - Put this part at the top of start() function
        // Do not use _hardware_info directry since this data is located in UEFI-app space
        hardware_info = *_hardware_info;
        init_segmentation();
        init_virtual_memory();
        init_intr();
        init_console(&hardware_info.fb);
        init_acpi_pm_timer(hardware_info.rsdp);
        page_allocator_init();
        init_ramdisk();
        init_fs();
        init_virtual_memory();
        init_process();

        // To here - Put this part at the top of start() function
        for (unsigned int i = 0; i < hardware_info.fb.height; i++) {
                for (unsigned int j = 0; j < hardware_info.fb.width; j++) {
                        struct Pixel *pixel = hardware_info.fb.base + hardware_info.fb.width * i + j;
                        // † AYAME †
                        pixel->r = 111;
                        pixel->g = 51;
                        pixel->b = 129;
                }
        }

        // Do not delete this line!
        while (1) {
                asm volatile ("hlt");
        }
}
