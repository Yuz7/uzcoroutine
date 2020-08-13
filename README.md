# uzcoroutine
汇编实现简单的非对称有栈协程库
* 目前仅支持x86_64架构
* 使用状态机判断协程运行状态来控制相关逻辑
* cocontext.S用汇编实现了上下文获取与上下文切换，忽略浮点数和信号的切换
* coctx实现了保存上下文的数据结构和用于上下文初始化的make函数
* uzcoroutine实现了resume和yield等方法，为协程库的主要逻辑


不使用ucontext主要原因是osx取消了ucontext（公司电脑与云服务器系统不一样QAQ），故对于mac选手可以考虑实现汇编的上下文切换，同时也可以适配其他x86_64架构的机子

### ucontext
coctx中的ucontext为保存上下文的数据结构，仅使用14个寄存器，不对浮点数和信号进行上下文的保存
![ucontext](https://github.com/Yuz7/uzcoroutine/blob/master/pic/uctx_pic.png)


### co_make、co_swap
协程在resume中直接使用co_make进行初始化，使用状态机来判断运行状态进行相应的切换。
co_make初始化最关键的设置了ret addr、rdi、rsi，当切换完成时co_swap会将regs[12]即ret addr压入栈中，当ret时会使用栈中最后一个地址作为rip指令，同时利用保存的rdi和rsi作为参数，实现了初始的运行函数，该项目初始化函数为mainfunc
![makeswap](https://github.com/Yuz7/uzcoroutine/blob/master/pic/make_swap.png)


## 后续
该项目简单的实现了一个非共享栈的协程库，后续会实现共享栈版本的协程库，即实现一个save_stack的函数

## 相关参考
云风/coroutine
linux/ucontext
Tencent/libco
alibaba/coobjc
