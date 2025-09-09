#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct COLOR
{
    uint32_t hex_code;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} __attribute__((packed));

struct PALETTE
{
    struct COLOR colors[256];
};

extern struct PALETTE color_palette;

void create_palette();
struct COLOR get_color(int code);
uint32_t get_colorh(int code);