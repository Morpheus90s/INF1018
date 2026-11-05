#include "fp.h"

float float2(float f) {
    U u;
    u.f = f;
    unsigned int ui = u.i;

    unsigned int s = getsig(ui);
    unsigned int exp = getexp(ui);
    unsigned int frac = getfrac(ui);

    if (exp == 0xff) {
        return f;
    }

    if (exp == 0) {
        frac <<= 1;
    }
    else {
        exp++;
        if (exp == 0xff) {
            frac = 0; 
        }
    }

    u.i = makefloat(s, exp, frac);
    return u.f;
}

float int2float(int i) {
    if (i == 0) {
        return 0.0f;
    }

    unsigned int s = 0;
    unsigned int val_abs;

    if (i < 0) {
        s = 1;
        val_abs = (unsigned int)(-i);
    } else {
        s = 0;
        val_abs = (unsigned int)i;
    }

    int pos_bit = 31;
    while ((val_abs & (1U << pos_bit)) == 0) {
        pos_bit--;
    }

    unsigned int exp = pos_bit + 127;

    unsigned int frac;
   
    if (pos_bit <= 23) {
        frac = (val_abs << (23 - pos_bit)) & 0x7fffff;
    } else {
        frac = (val_abs >> (pos_bit - 23)) & 0x7fffff;
    }

    U u;
    u.i = makefloat(s, exp, frac);
    return u.f;
}
