#pragma once

int disk_read(char *buf, int block_no);
int disk_write(char *buf, int block_no);
void init_ramdisk(void);
