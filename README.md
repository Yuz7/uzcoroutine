# uzcoroutine
汇编实现简单的非对称有栈协程库
* 目前仅支持x86_64架构
* cocontext.S用汇编实现了上下文获取与上下文切换
* coctx主要为上下文的数据结构和上下文的初始化make
* uzcoroutine实现了resume和yield等方法，为协程库的主要逻辑
不使用ucontext主要原因是osx取消了ucontext（公司电脑与云服务器系统不一样QAQ），故对于mac选手可以考虑实现汇编的上下文切换，同时也可以适配其他x86_64架构的机子

## 主要数据结构
### ucontext
coctx中的ucontext为保存上下文的数据结构，仅使用14个寄存器，不对浮点数和信号进行上下文的保存。
