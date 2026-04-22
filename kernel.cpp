#include "kernel.h";



using uint8  = unsigned char;
using uint32 = unsigned int;
using usize  = uint32;

extern "C" char __bss[], __bss_end[], __stack_top[];

extern "C" void* memset(void* buf, int c, usize n) {
    uint8* p = (uint8*)buf;
    while (n--) {
        *p++ = (uint8)c;
    }
    return buf;
}

extern "C" void kernel_main() {
    memset(__bss, 0, (usize)(__bss_end - __bss));
    for (;;) {
    }
}

extern "C" __attribute__((section(".text.boot")))
__attribute__((naked))
void boot(void) {
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n"
        "j kernel_main\n"
        :
        : [stack_top] "r"(__stack_top)
    );
}