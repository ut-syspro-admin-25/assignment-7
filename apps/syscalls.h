#pragma once

unsigned long long syscall_puts(const char *s);
int syscall_getpid(void);
int syscall_fork(void);
int syscall_wait(int *ret);
int syscall_exit(int ret);
int syscall_read(char *buf, int n);
int syscall_exec(char *buf);
