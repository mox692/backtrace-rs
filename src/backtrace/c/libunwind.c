#include<stdio.h>
#include<stdlib.h>
#include "unwind.h"

// header import
_Unwind_Reason_Code _Unwind_Backtrace(_Unwind_Trace_Fn fn, void *trace_parameter);
// header import
uintptr_t _Unwind_GetIP(struct _Unwind_Context *context);
// header import
void *_Unwind_FindEnclosingFunction(void *pc);



_Unwind_Reason_Code trace_fn(_Unwind_Context *ctx, void *arg) {
    printf("called trace!!, args is %d\n", *((int*)arg));

    uintptr_t unwind_ip = _Unwind_GetIP(ctx);

    // will not work
    void *try_fn_addr = _Unwind_FindEnclosingFunction((void*) unwind_ip);

    struct dwarf_eh_bases *dwarf = malloc(sizeof(struct dwarf_eh_bases));

    // MEMO:
    // what is FDE? 
    //   https://llvm.org/doxygen/classllvm_1_1dwarf_1_1FDE.html
    // eh_frame
    //   https://refspecs.linuxfoundation.org/LSB_3.0.0/LSB-Core-generic/LSB-Core-generic/ehframechpt.html
    _Unwind_Find_FDE((void*) unwind_ip, (void*) dwarf);



    printf("unwind_ip  : %p (%lu)\n", unwind_ip, unwind_ip);
    printf("try_fn_addr: %p (%lu)\n", try_fn_addr, try_fn_addr);
    printf("dwarf->func: %p (%lu)\n", dwarf->func, dwarf->func);

    return _URC_NO_REASON;
}

void baz() {
    int a = 1;
    _Unwind_Backtrace(trace_fn, &a);
}

void bar() {
    baz();
}

void foo() {
    bar();
}

int main() {
    printf("-------------\n", (void*)main);
    printf("main addr:     %p\n", (void*)main);
    printf("foo  addr:     %p\n", (void*)foo);
    printf("bar  addr:     %p\n", (void*)bar);
    printf("baz  addr:     %p\n", (void*)baz);
    printf("unwind addr:   %p\n", (void*)_Unwind_FindEnclosingFunction);
    printf("trace_fn addr: %p\n", (void*)trace_fn);
    printf("-------------\n", (void*)main);

    bar();
    return 0;
}
