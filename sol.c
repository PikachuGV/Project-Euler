/*
It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.
Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
*/

/*
We can deduce some facts about x.
1. We know if x is odd, it must contain a 5. If it is even, it must contain a 0.
2. We also know that if x is n digits long, x < 10^n / 6.

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int TENS[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

bool sameDigits(int a, int b, int d) {
    int A[d], B[d];
    for (int i = d - 1; i >= 0; i--) {
        A[i] = a % 10; B[i] = b % 10;
        a /= 10; b /= 10;
    }
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (A[i] == B[j]) {B[j] = -1; break;}
        }
    }

    for (int i = 0; i < d; i++) {
        if (B[i] != -1) return false;
    }
    return true;
}

bool hasD(int n, int d) {
    while (n != 0) {
        if (n % 10 == d) return true;
        n /= 10;
    }
    return false;
}

int main() {


    return 0;
}