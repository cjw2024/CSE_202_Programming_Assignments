#include <stdio.h>

int mul3div4(int x) {
    int mul = x + (x << 1);  // 3 * x using bit shifting
    return mul >> 2;  // divide by 4 using bit shifting
}

int tsub_ok(int x, int y) {
    int sign_x = (x >> 31) & 1; // isolate sign of x
    int sign_y = (y >> 31) & 1; // isolate sign of y
    int sign_diff = ((x - y) >> 31) & 1;  // isolate the sign of the difference
    return !((sign_x ^ sign_y) & (sign_x ^ sign_diff));  // check if the signs still match
}

int main() {
    int x = 8;
    printf("mul3div4(%d) = %d\n", x, mul3div4(x));

    int y = -2147483647;
    int z = 100000000;
    printf("tsub_ok(%d, %d) = %d\n", y, z, tsub_ok(y, z));
    return 0;
}
