#ifndef _BMP_H
#define _BMP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "math.h"
#include "memory.h"

struct bmp_header
{
    uint8_t Type[2];            //File Type : set to "BM"
    uint32_t Size;              //size in BYTES of the file
    uint32_t Reserved;          //reserved : set to 0
    uint32_t Offset;            //offset to data
    uint32_t HeaderSize;        //always 40
    uint32_t Width;             //width of bitmap
    uint32_t Height;            //height of bitmap
    uint16_t Planes;            //Number of PLanes : set to 1
    uint16_t BPP;               //Number of Bits Per Pixel
    uint32_t Compression;       //Compression, usually 0
    uint32_t SizeImage;         //size in bytes
    uint32_t XPixelsPerMeter;   //horizontal pixels per meter
    uint32_t YPixelsPerMeter;   //vertical pixels per meter
    uint32_t ColorsUsed;        //number of colors used
    uint32_t ColorsImportant;   //number of "important" colors
};



#endif