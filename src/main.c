#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "util/util.h"

#include "bootloader/limine_requests.h"
#include "fpu/fpu.h"
#include "sys/acpi/acpi.h"
#include "driver/vga/color.h"
#include "driver/vga/vga.h"

// If renaming kmain() to something else, make sure to change the linker script accordingly.
void kmain(void) 
{
    //initalize VGA
    init_VGA();

    //initialize RSDP
    init_RSDP();

    cls(0x00FFFF);
    draw_rect(0, framebuffer->height-65, framebuffer->width, 65, true, 0xFF0000);
    draw_text(10, 10, "> Hello! Welcome to Yggdrasil OS!", 0x000000);
    hcf();
}
