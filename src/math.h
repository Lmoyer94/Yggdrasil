#ifndef _MATH_H
#define _MATH_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int64_t abs(int64_t value)
{
    if (value < 0)
        return -value;
    else
        return value;
}

#endif