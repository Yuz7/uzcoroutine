//@Author Yuz
#include "uzcoroutine.h"
#include <assert.h>
#include <iostream>
extern "C"
{
    extern void co_swap(ucontext*, ucontext*) asm("co_swap");
    extern void co_getcontext(ucontext*) asm("co_getcontext");
};

schedule* coroutine_open()
{
    schedule *sch = new schedule();
    return sch;
}

uzcoroutine* _co_new(schedule*S,coroutine_func fun,void *tud)
{
    uzcoroutine*co = new uzcoroutine(fun,tud,S);
    return co;
}

void coroutine_close(schedule*S)
{
	for(int i = 0; i < S->cap;i++){
		uzcoroutine*co = S->co[i];
		if(co){
			delete co;
		}
	}
	free(S->co);
	S->co = NULL;
	delete S;
}

int coroutine_new(schedule*S,coroutine_func fun,void *tud)
{
    uzcoroutine*co = _co_new(S,fun,tud);
    if(S->nco == S->cap)
    {
        int id = S->cap;
        S->co = static_cast<uzcoroutine **>(realloc(S->co, S->cap * 2 * sizeof(struct coroutine*)));
        memset(S->co + S->cap, 0, sizeof(struct coroutine *) * S->cap);
        S->co[S->cap] = co;
        S->cap *= 2;
        ++S->nco;
        return id;
    } else {
        for(int i = 0; i < S->cap; i++){
            int id = (S->nco+i) % S->cap;
            if(S->co[id] == NULL){
                S->co[id] = co;
                ++S->nco;
                return id;
            }
        }
    }
    assert(0);
    return -1;
}

int coroutine_status(schedule *S, int id)
{
    assert(id >= 0 && id < S->cap);
    if(S->co[id] == NULL){
        return COROUTINE_DEAD;
    }
    return S->co[id]->status;
}

void co_main_yield(schedule*S);

void
mainfunc(void*arg)
{
	schedule*S = (schedule*)arg;
	int id = S->running;
	uzcoroutine*C = S->co[id];
	C->func(S,C->ud);
	co_main_yield(S);
}

void coroutine_resume(schedule *S, int id)
{
    assert(S->running == -1);
    assert(id >= 0 && id < S->cap);
    uzcoroutine *C = S->co[id];
    if(C == NULL)
        return;
    int status = C->status;
    switch(status){
    case COROUTINE_READY:
       // co_getcontext(&C->ctx);
	S->running = id;
        C->status = COROUTINE_RUNNING;
        coctx_make(&C->ctx,mainfunc,S,0);
	co_swap(&S->main,&C->ctx);
        break;
    case COROUTINE_SUSPEND:
        S->running = id;
	C->status = COROUTINE_RUNNING;
	co_swap(&S->main,&C->ctx);
	break;
    default:
        assert(0);
    }
}

void coroutine_yield(schedule * S)
{
    int id = S->running;
    assert(id >= 0);
    uzcoroutine * co = S->co[id];
    co->status = COROUTINE_SUSPEND;
    S->running = -1;
    co_swap(&co->ctx,&S->main);
}

void co_main_yield(schedule*S)
{
    int id = S->running;
    assert(id>=0);
    uzcoroutine*co = S->co[id];
    co->status = COROUTINE_READ;
    S->running = -1;
    co_swap(&co->ctx,&S->main);
}
