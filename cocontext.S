
#if defined(__x86_64__)

.global co_getcontext
co_getcontext:
    movq %rbx,   (%rdi)
    movq %rbp,  8(%rdi)
    movq %r12, 16(%rdi)
    movq %r13, 24(%rdi)
    movq %r14, 32(%rdi)
    movq %r15, 40(%rdi)
    movq %rdi, 56(%rdi)
    movq %rsi, 64(%rdi)
    movq %rdx, 72(%rdi)
    movq %rcx, 80(%rdi)
    movq %r8,  88(%rdi)
    movq %r9,  96(%rdi)
    movq %rsp,104(%rdi)
    movq %rsp,112(%rdi)
    addq $8,  112(%rsp)
    ret

.global co_swap
co_swap:
    leaq 8(%rsp),%rax
    leaq 112(%rdi),%rsp

    pushq %rax
    pushq -8(%rax)
    pushq %r9
    pushq %r8
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    pushq %r15
    pushq %r14
    pushq %r13
    pushq %r12
    pushq %rbp
    pushq %rbx

    movq %rsi, %rsp

    popq %rbx
    popq %rbp
    popq %r12
    popq %r13
    popq %r14
    popq %r15
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    popq %r8
    popq %r9
    popq %rax
    popq %rsp

    pushq %rax

    xorl %eax,%eax

    ret

#endif
