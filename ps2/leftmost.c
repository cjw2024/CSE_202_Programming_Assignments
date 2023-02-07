#include <stdio.h>

int leftmost_one(unsigned x) {
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x - (x >> 1);
}

int main(void) {
    unsigned x = 0xFF00;
    printf("0x%x\n", leftmost_one(x));
    return 0;
}