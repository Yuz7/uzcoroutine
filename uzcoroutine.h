// @Author Yuz

#ifndef __UZCOROUTINE_H__
#define __UZCOROUTINE_H__
#include "coctx.h"
#include <stddef.h>
#include <string.h>

#define STACK_SIZE (128*1024)
#define DEFAULT_COROUTINE 16

enum
{
    COROUTINE_DEAD = 0,
    COROUTINE_READY,
    COROUTINE_RUNNING,
    COROUTINE_SUSPEND
};

struct uzcoroutine;

struct schedule{
    ucontext main;
    int nco;
    int cap;
    int running;
    uzcoroutine **co;

    schedule():nco(0),cap(DEFAULT_COROUTINE),running(-1){
        co = static_cast<uzcoroutine **>(malloc(sizeof(struct uzcoroutine *) * cap));
        memset(co, 0, sizeof(struct uzcoroutine *) * cap);
    };
};

typedef void (*coroutine_func)(schedule*S,void*ud);

struct uzcoroutine{
    coroutine_func func;
    void            *ud;
    ucontext        ctx;
    schedule       *sch;
    int          status;
    char         stack[STACK_SIZE];

    uzcoroutine(coroutine_func fun,void *tud,schedule *S):
            func(fun),ud(tud),sch(S),status(COROUTINE_READY){
		ctx.ss_sp = stack;
		ctx.ss_size = STACK_SIZE;
	};
};

struct schedule * coroutine_open(void);
void coroutine_close(struct schedlue *);

int coroutine_new(struct schedule *, coroutine_func, void *ud);
void coroutine_resume(struct schedule *, int id);
int coroutine_status(struct schedule *, int id);
int coroutine_running(struct schedule *);
void coroutine_yield(struct schedule *);



#endif
