#include "color.h"

struct PALETTE color_palette;

struct COLOR create_color(uint8_t r, uint8_t g, uint8_t b)
{
    struct COLOR c;
    c.hex_code = 0;
    c.red = r;
    c.green = g;
    c.blue = b;
    c.alpha = 255;

    c.hex_code |= (uint32_t)c.alpha << (8*3);
    c.hex_code |= (uint32_t)c.red << (8*2);
    c.hex_code |= (uint32_t)c.green << (8);
    c.hex_code |= (uint32_t)c.blue;

    return c;
}

void create_palette()
{
    int num = 0;
    //black, 14 grey, and white
    for (int i = 0; i <= 256; i += 16)
    {
        if (i == 256)
            i = 255;
        color_palette.colors[num++] = create_color(i, i, i);
    }

    //reds
    for (int i = 0; i <= 256; i += 16)
    {
        if (i == 256)
            i = 255;
        color_palette.colors[num++] = create_color(i, 0, 0);
    }

    //greens
    for (int i = 0; i <= 256; i += 16)
    {
        if (i == 256)
            i = 255;
        color_palette.colors[num++] = create_color(0, i, 0);
    }

    //blues
    for (int i = 0; i <= 256; i += 16)
    {
        if (i == 256)
            i = 255;
        color_palette.colors[num++] = create_color(0, 0, i);
    }

    //red_green
    for (int i = 0; i <= 256; i += 32)
    {
        if (i == 256)
            i = 255;

        for (int j = 0; j <= 256; j += 32)
        {
            if (j == 256)
                j = 255;

            color_palette.colors[num++] = create_color(i, j, 0);
        }
    }

    //red_blue
    for (int i = 0; i <= 256; i += 32)
    {
        if (i == 256)
            i = 255;

        for (int j = 0; j <= 256; j += 32)
        {
            if (j == 256)
                j = 255;

            color_palette.colors[num++] = create_color(i, 0, j);
        }
    }


    //green blue
    for (int i = 0; i <= 256; i += 32)
    {
        if (i == 256)
            i = 255;

        for (int j = 0; j <= 256; j += 32)
        {
            if (j == 256)
                j = 255;

            color_palette.colors[num++] = create_color(0, i, j);
        }
    }
}

struct COLOR get_color(int code)
{
    return color_palette.colors[code];
}

uint32_t get_colorh(int code)
{
    return color_palette.colors[code].hex_code;
}