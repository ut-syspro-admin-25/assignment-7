#pragma once

struct Process;
struct App;

void init_virtual_memory();
void load_process_pagetable(struct Process *process);
void init_process_pagetable(struct Process *process, struct App *app);

#define USERSTACK_BOTTOM        (0xffff810000000000)
#define USERSTACK_TOP           (USERSTACK_BOTTOM+0x1000)
