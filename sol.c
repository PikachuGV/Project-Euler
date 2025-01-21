/*
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which, a^2 + b^2 = c^2.
For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2. 
There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int squares[1001];
    for (int i = 0; i < 1001; i++) {
        squares[i] = i * i;
    }

    int f = 0;
    int a, b, c;
    bool done = false;

    while (f < 1001 && !done) {
        a = squares[f];
        for (int i = f + 1; i < 1001; i++) {
            if (1000 - i - f >= 1001) continue;
            b = squares[i]; c = a + b;
            if (c == squares[1000 - f - i]) {
                printf("%d\n", f * i * (1000 - f - i));    
            }
        }
        f++;
    }

    return 0;
}