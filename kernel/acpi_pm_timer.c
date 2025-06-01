#include "kernel.h"
#include "hardware.h"
#include "console.h"
#include "util.h"

static struct XSDT *xsdt;
static unsigned int PM_TMR;
static bool pm_tmr_32bit;

static void *xsdt_find(const char *sig)
{
        struct SDTH *header = (struct SDTH *)xsdt;
        struct SDTH *ent;
        unsigned int nentry;

        nentry = (header->length - sizeof (*header)) / sizeof (unsigned long long);

        for (unsigned int i = 0; i < nentry; i++) {
                ent = (struct SDTH *)xsdt->other_tables[i];
                if (!strncmp (ent->signature, sig, 4))
                        return ent;
        }
        return NULL;
}

#define PM_FREQ_HZ      3579545
#define CNT_MASK        (pm_tmr_32bit ? 0xFFFFFFFF : 0xFFFFFF)

void pm_timer_sleep(unsigned int ms)
{
        uint32_t base, waitcnt = 0, now;
        uint32_t clock = ms * PM_FREQ_HZ / 1000;

        base = inl(PM_TMR);

        while (waitcnt < clock) {
                now = inl(PM_TMR);
                waitcnt += base > now ? CNT_MASK - base + now
                                      : now - base;
                base = now;
        }
}

void init_acpi_pm_timer(struct RSDP *rsdp)
{
        struct FADT *fadt;

        if (strncmp(rsdp->signature, "RSD PTR ", 8))
                return;

        xsdt = (struct XSDT *)rsdp->xsdt_address;

        fadt = xsdt_find("FACP");
        if (!fadt)
                return;

        PM_TMR = fadt->PM_TMR_BLK;
        pm_tmr_32bit = !!(fadt->flags & (1 << 8));
}
