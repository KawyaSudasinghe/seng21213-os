#include "vga.h"
#include <process.h>

void task_a(void) {
    while (1) {
        vga_puts(" [Task A] ");
        for (volatile int i = 0; i < 10000000; i++);
        yield();
    }
}

void task_b(void) {
    while (1) {
        vga_puts(" [Task B] ");
        for (volatile int i = 0; i < 10000000; i++);
        yield();
    }
}

void kernel_main(void) {
    vga_clear(0);
    vga_puts("Initializing Stage 1 Scheduler...\n");

    process_init();
    process_create(task_a);
    process_create(task_b);

    vga_puts("Starting multitasking:\n");
    yield();

    while (1);
}
