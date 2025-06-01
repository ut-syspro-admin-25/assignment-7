#include "kernel.h"
#include "fs.h"
#include "ramdisk.h"
#include "page_allocator.h"
#include "util.h"
#include "console.h"

struct SuperBlock superblock;
struct BlockGroupDesc bg_desc;

static void init_superblock()
{
        disk_read((char *)&superblock, 1);
}

static void init_bg_desc()
{
        disk_read((char *)&bg_desc, 2);
}

static void inode_get(struct Inode *ino, int inum)
{
        ;
}

#define inode_nblock(_i) ((_i)->i_blocks / (BSIZE/512))

static char *get_block(struct Inode *ino, int bnum)
{
        return NULL;
}

static int search_dirent(char *blk, char *path)
{
        return -1;
}

static int inode_search(struct Inode *dir_inode, char *name)
{
        return -1;
}

static void get_rootinode(struct Inode *ino)
{
        inode_get(ino, EXT2_ROOT_INO);
}

static int read_inode(struct Inode *ino, char *buf, uint64_t off, uint64_t size)
{
        return -1;
}

int read_file(char *name, char *buf)
{
        return -1;
}

void init_fs(void)
{
        init_superblock();
        init_bg_desc();

        if (superblock.s_magic != 0xef53) {
                // not ext2 filesystem!
                return;
        }
}
