//@Author Yuz

#include <stdlib.h>

typedef void (*coctx_func)(void *arg);

struct ucontext
{
    void *regs[14];
    char *ss_sp;       //stack pointer
    size_t ss_size;     //stack size
};

int coctx_init(ucontext *ctx);
void coctx_make(ucontext *ctx, coctx_func fun,void * s1, void * s2);

