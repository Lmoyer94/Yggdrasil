#include <stdbool.h>

// ASM Functions
extern bool _enable_SSE();  //enabled SSE features
extern bool _enable_AVX();  //enabled AVX features

extern bool _disable_AVX(); //used to disable AVX features for supposedly faster context switches

// C functions
void enable_sse();
void enable_fpu();
void disable_fpu();