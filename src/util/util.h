#ifndef _UTIL_H
#define _UTIL_H

#include "../bootloader/limine_requests.h"

#include "../driver/vga/vga.h"

static void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

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

    cls(0x00FFBE);
    draw_text(x, y, message, 0x000000);

    hcf();
}
#endif