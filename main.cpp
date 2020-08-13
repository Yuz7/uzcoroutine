#include "uzcoroutine.h"
#include <iostream>
/*
extern "C"
{
    extern void co_swap(ucontext*, ucontext*) asm("co_swap");
    extern void co_getcontext(ucontext*) asm("co_getcontext");
};*/

static void
fun(schedule *S,void *ud)
{
    int *a = static_cast<int *>(ud);
    for(int i = 1;i <=10; i++){    
	std::cout << "a: " << *a << " " << std::endl;	
    	coroutine_yield(S);
    }
}
/*
static void
mainfunc(void*arg)
{
	schedule*S = (schedule*)arg;
	int id = S->running;
	uzcoroutine*C = S->co[id];
	C->func(S,C->ud);
	std::cout << "debug1" << std::endl;
	delete C;
	S->co[id] = NULL;
	S->running = -1;
	std::cout << "debug2" << std::endl;
}*/

int main()
{
    int a1 = 0;
    int a2 = 1;
    schedule* S = coroutine_open();
    int co1 = coroutine_new(S,fun, &a1);
    int co2 = coroutine_new(S,fun, &a2);
    while(coroutine_status(S,co1)&& coroutine_status(S,co2)){
	coroutine_resume(S,co1);
    	coroutine_resume(S,co2);
    }
    /* if(coroutine_status(S,co1) == COROUTINE_READY){
       std::cout << "co1."
        std::cout << "cap: " << S->cap << std::endl;
        std::cout << "nco: " << S->nco << std::endl;
    }*/
/*
    uzcoroutine* co = S->co[co1];
    ucontext* cotx = &co->ctx;
    S->running = co1;
    coctx_make(cotx,mainfunc,S,0);
   // coroutine_func f = (coroutine_func)cotx->regs[12];
   // f(co->sch,co->ud);
    co_swap(&S->main,cotx);
*/
    std::cout << "----the end----" << std::endl ;
    
    return 0;
}
