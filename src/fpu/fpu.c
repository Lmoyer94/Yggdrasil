#include "fpu.h"

//which technologies are supported?
bool SSE = false, SSE2 = false, SSSE3 = false;
bool SSE4_1 = false, SSE4_2 = false, SSE4_A = false, SSE5 = false; 
bool AVX = false, AVX2 = false, AVX512 = false;
bool XOP = false, FMA4 = false, CVT16 = false;  //SSE5 units

//are we enabled?
bool sse_enabled = false;
bool avx_enabled = false;


void enable_sse()
{
    switch (_enable_SSE())
    {
        case 7:     SSE5 = true; XOP = true;            //SSE5: XOP included
                    SSE4_A = SSE4_2 = SSE4_1 = SSSE3 = SSE2 = SSE = true; break;

        case 8:     SSE5 = true; FMA4 = true;           //SSE5: FMA4 included
                    SSE4_A = SSE4_2 = SSE4_1 = SSSE3 = SSE2 = SSE = true; break;

        case 9:     SSE5 = true; CVT16 = true;          //SSE5: CVT16 included
                    SSE4_A = SSE4_2 = SSE4_1 = SSSE3 = SSE2 = SSE = true; break;

        case 10:    SSE5 = true; XOP = true; FMA4 = true;   //SSE5: XOP, FMA4, included
                    SSE4_A = SSE4_2 = SSE4_1 = SSSE3 = SSE2 = SSE = true; break;

        case 11:    SSE5 = true; FMA4 = true; CVT16 = true; //SSE5: FMA4, CVT16 included
                    SSE4_A = SSE4_2 = SSE4_1 = SSSE3 = SSE2 = SSE = true; break;

        case 12:    SSE5 = true; XOP = true; FMA4 = true; CVT16 = true; //SSE5: XOP, FMA4, CVT16 all included
                    SSE4_A = SSE4_2 = SSE4_1 = SSSE3 = SSE2 = SSE = true; break;

        case 6:     SSE4_A = true;  //SSE4_A
        case 5:     SSE4_2 = true;  //SSE4_2
        case 4:     SSE4_1 = true;  //SSE4_1
        case 3:     SSSE3 = true;   //SSSE3
        case 2:     SSE2 = true;    //SSE2
        case 1:     SSE = true;     //SSE
        case 0:     break;          //SSE not possible
        default:    break;  //what?
    }

    if (!SSE)
        sse_enabled = false;
    else
        sse_enabled = true;
    return true;
}

void enable_fpu()
{
    switch (_enable_AVX())
    {
        case 3:     AVX512 = true;
        case 2:     AVX2 = true;
        case 1:     AVX = true; break;
    
        case 0:     break;  //no AVX
        default:    break; //WHAT?
    }

    if (!AVX)
        avx_enabled = false;
    else
        avx_enabled = true;
}

void disable_fpu()
{
    _disable_AVX();
    avx_enabled = false;
}