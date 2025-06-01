#include "kernel.h"
#include "util.h"
#include "ramdisk.h"

extern char _binary____fs_img_start[];

static void *disk_base;

int disk_read(char *buf, int block_no)
{
        int offset;

        offset = block_no * 1024;
        memcpy (buf, disk_base + offset, 1024);

        return 0;
}

int disk_write(char *buf, int block_no)
{
        int offset;

        offset = block_no * 1024;
        memcpy (disk_base + offset, buf, 1024);

        return 0;
}

void init_ramdisk(void)
{
        disk_base = _binary____fs_img_start;
}
