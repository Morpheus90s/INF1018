#ifndef FP_H
#define FP_H

typedef union { 
    float f;
    unsigned int i;
} U;

#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))
#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)

float float2(float f);
float int2float(int i);

#endif
