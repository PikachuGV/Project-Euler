/*
The first two consecutive numbers to have two distinct prime factors are:

14 = 2 * 7
15 = 3 * 5.

The first three consecutive numbers to have three distinct prime factors are:

644 = 2^2 * 7 * 23
645 = 3 * 5 * 43
646 = 2 * 17 * 19.

Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int ndpf(int n) {
    int c = 0;
    if (n % 2 == 0) {
        c++;
        while (n % 2 == 0) n >>= 1;
    }
    for (int p = 3; p <= n; p += 2) {
        if (n % p == 0) {
            c++;
            while (n % p == 0) n /= p;
        }
    }
    return c;
}

int main() {
    int chainHead = 0, chainLength = 0;
    for (int i = 210; i < 1000000; i++) {
        if (ndpf(i) == 4) {
            if (chainLength == 0) chainHead = i;
            chainLength++;
            if (chainLength == 4) {printf("%d\n", chainHead);break;}
        } else {
            chainLength = 0; chainHead = 0;
        }
    }

    return 0;
}