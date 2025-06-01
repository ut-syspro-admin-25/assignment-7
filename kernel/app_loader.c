#include "kernel.h"
#include "process.h"
#include "memory.h"
#include "page_allocator.h"
#include "util.h"
#include "console.h"
#include "elf.h"
#include "app_loader.h"

int app_elf_parse(struct App *app, char *appname, void *elf_start)
{
        struct Ehdr *ehdr = (struct Ehdr *)elf_start;
        struct Phdr *phdr;
        void *program_start;
        uint64_t program_size, load_start;
        uint64_t phoff;

        if (!iself(ehdr))
                goto err;
        if (ehdr->e_type != ET_EXEC)
                goto err;

        phoff = ehdr->e_phoff;
        for (int i = 0; i < ehdr->e_phnum; i++, phoff += sizeof phdr) {
                phdr = (struct Phdr *)(elf_start + phoff);
                if (phdr->p_type != PT_LOAD)
                        continue;

                program_start = elf_start + phdr->p_offset;
                load_start = phdr->p_vaddr;
                program_size = phdr->p_filesz;
                break;
        }

        app->elf_program_start = (uint64_t)program_start;
        app->program_size = program_size;
        app->load_start = load_start;
        app->entrypoint = ehdr->e_entry;
        strcpy(app->name, appname);

        return 0;

err:
        app->elf_program_start = 0;
        app->program_size = 0;
        app->load_start = 0;
        app->entrypoint = 0;
        return -1;
}
