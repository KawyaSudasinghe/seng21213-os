#include "vga.h"
#include <process.h>
#include <idt.h>
#include <timer.h>

static inline void enable_interrupts(void) {
    __asm__ volatile ("sti");
}

void task_a(void) {
    while (1) {
        vga_puts(" [A] ");
        for (volatile int i = 0; i < 5000000; i++);
    }
}

void task_b(void) {
    while (1) {
        vga_puts(" [B] ");
        for (volatile int i = 0; i < 5000000; i++);
    }
}

void kernel_main(void) {
    vga_clear(0);
    vga_puts("Initializing Stage 2 Preemptive Scheduler...\n");

    idt_init();
    timer_init(100); // Set 100 Hz timer frequency

    process_init();
    process_create(task_a);
    process_create(task_b);

    vga_puts("Enabling Interrupts...\n");
    enable_interrupts();

    while (1);
}
