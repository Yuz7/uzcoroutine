#include "coctx.h"
#include <string.h>


/*
    regs[13] -> exclude ret addr
    regs[12] -> ret addr
    regs[11] -> r9
    regs[10] -> r8
    regs[9]  -> rcx
    regs[8]  -> rdx
    regs[7]  -> rsi
    regs[6]  -> rdi
    regs[5]  -> r15
    regs[4]  -> r14
    regs[3]  -> r13
    regs[2]  -> r12
    regs[1]  -> rbp
    regs[0]  -> rbx

*/

enum
{
    kRDI = 6,
    kRSI = 7,
    kRET = 12,
    kRSP = 13,
};

int coctx_init(ucontext*ctx){
    memset(ctx,0,sizeof(*ctx));
    return 0;
}

void coctx_make(ucontext*ctx,coctx_func fun, void *s1, void *s2)
{
    char *sp = ctx->ss_sp + ctx->ss_size;
    sp = (char *) ((unsigned long)sp & -16LL );

    memset(ctx->regs,0 , sizeof(ctx->regs));

    ctx->regs[kRSP] = sp - 8;

    ctx->regs[kRET] = (char *)fun;

    ctx->regs[kRDI] = (char *)s1;
    ctx->regs[kRSI] = (char *)s2;

}


