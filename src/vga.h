#ifndef _VGA_H
#define _VGA_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../../limine/limine.h"

#include "math.h"
#include "memory.h"
#include "vga_font.h"

struct limine_framebuffer *framebuffer;

void draw_pixel(uint64_t x, uint64_t y, uint32_t color)
{
    volatile uint32_t* fb_ptr = framebuffer->address;
    fb_ptr[(y * framebuffer->width) + x] = color;
}

void clear_screen(uint32_t color)
{
    for (uint32_t y = 0; y < framebuffer->height; y++)
    {
        for (uint32_t x = 0; x < framebuffer->width; x++)
        {
            draw_pixel(x, y, color);
        }
    }
}

void draw_line(uint64_t x0, uint64_t y0, uint64_t x1, uint64_t y1, uint32_t color)
{
    int64_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int64_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int64_t err = dx + dy, e2;

    for (;;)
    {   
        draw_pixel(x0, y0, color);

        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx;}
        if (e2 <= dx) { err += dx; y0 += sy;}
    }
}


void draw_image(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t* data)
{
    for (uint64_t dy = 0; dy < height; dy++)
    {
        for (uint64_t dx = 0; dx < width; dx++)
        {
            uint32_t color = data[(dy*width) + dx];
            draw_pixel(x+dx, y+dy, color);
        }
    }
}

void draw_char(int x, int y, char ch, uint32_t color)
{
    if ((unsigned)ch >= 128) return;
    const uint8_t *glyph = font8x8[(int)ch];
    for (int row = 0; row < 8; row++)
    {
        uint8_t bits = glyph[row];
        for (int col = 0; col < 8; col++)
        {
            if (bits & (1 << col))
            {
                draw_pixel(x + col, y + row, color);
            }
        }
    }
}

void draw_text(uint64_t x, uint64_t y, const char* str, uint32_t color)
{
    while (*str)
    {
        draw_char(x, y, *str++, color);
        x += 8;
    }
}

#endif