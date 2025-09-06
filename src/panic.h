#ifndef _KERNEL_PANIC_H
#define _KERNEL_PANIC_H

#include "acpi.h"
#include "vga.h"

// Halt and catch fire function.
static void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

// Orangish screen of death. Synonymous with Window's blue screen of death.
static void kpanic(const char* message)
{
    uint64_t len = 0;

    while (*message)
    {
        message++;
        len++;
    }

    message = message-len;

    uint64_t message_pixels = len * 8;

    uint64_t x = (framebuffer->width / 2) - (message_pixels / 2);
    uint64_t y = (framebuffer->height / 2)  - (8 / 2);

    clear_screen(0x00FFBE);
    draw_text(x, y, message, 0x000000);

    hcf();
}

#endif