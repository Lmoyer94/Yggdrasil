#ifndef _VGA_H
#define _VGA_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern struct limine_framebuffer *framebuffer;

void init_VGA();

void draw_pixel(uint64_t x, uint64_t y, uint32_t color);
void cls(uint32_t color);

void draw_line(uint64_t x0, uint64_t y0, uint64_t x1, uint64_t y1, uint32_t color);

void draw_rect(uint64_t x, uint64_t y, uint64_t width, uint64_t height, bool fill, uint32_t color);

void draw_circle(int64_t xm, int64_t ym, int64_t r, uint32_t color);

void draw_image(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t* data);

void draw_char(int x, int y, char ch, uint32_t color);
void draw_text(uint64_t x, uint64_t y, const char* str, uint32_t color);

#endif