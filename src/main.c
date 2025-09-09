#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../../limine/limine.h"

#include "util/util.h"

#include "fpu/fpu.h"
#include "driver/acpi.h"
#include "driver/vga/color.h"
#include "driver/vga/vga.h"

// Set the base revision to 3, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent, _and_ they should be accessed at least
// once or marked as used with the "used" attribute as done here.


__attribute__((used, section(".limine_requests")))
static volatile struct limine_rsdp_request rsdp_request =
{
    .id = LIMINE_RSDP_REQUEST,
    .revision = 1
};

// Finally, define the start and end markers for the Limine requests.
// These can also be moved anywhere, to any .c file, as seen fit.

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

// GCC and Clang reserve the right to generate calls to the following
// 4 functions even if they are not directly called.
// Implement them as the C specification mandates.
// DO NOT remove or rename these functions, or stuff will eventually break!
// They CAN be moved to a different .c file.

// If renaming kmain() to something else, make sure to change the linker script accordingly.
void kmain(void) 
{
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
    {
        hcf();
    }

/*
    //check for RSDP
    if (rsdp_request.response == NULL)
    {
        hcf();
    }
    else
    {
        rsdp_revision = rsdp_request.response->revision;
        if (rsdp_revision == 0)
        {
            rsdp_t = (struct RSDP_t*)&rsdp_request.response->address;
            xsdp_t = NULL;
        }
        else if (rsdp_revision >= 2)
        {
            rsdp_t = NULL;
            xsdp_t = (struct XSDP_t*)&rsdp_request.response->address;
        }

        init_RSDP();
    }
*/

    init_VGA();
    cls(0x00FFFF);
    draw_rect(0, framebuffer->height-65, framebuffer->width, 64, true, 0xFF00FF);
    hcf();
}
