#include <stdio.h>
#include <math.h>

#include "hexbin.h"

int main(int argc, char** argv){
    int num = argv[1];

    hex_bin(num);

}

void hex_bin(int x){

    printf("The number in hexadecimal: 0x");
  
    int i, bits = sizeof(x) * 8;
    for (i = bits / 4 - 1; i >= 0; i--) {
        int nibble = (x >> (i * 4)) & 0xF;
        if (nibble < 10) {
            printf("%d", nibble);
        } else {
            printf("%c", 'A' + nibble - 10);
        }
    }
    
    printf("\nThe number in binary: ");
    
    for (i = bits - 1; i >= 0; i--) {
            printf("%d", (x & (1 << i)) ? 1 : 0);
        if (i % 4 == 0)
            printf(" ");
    }
    
    printf("\n");

}