#pragma once

struct App {
        uint64_t entrypoint;
        uint64_t elf_program_start;
        uint64_t load_start;
        uint64_t program_size;
        char name[32];
};

int app_elf_parse(struct App *app, char *appname, void *start);
