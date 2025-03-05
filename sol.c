/*
Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.
37 36 35 34 33 32 31
38 17 16 15 14 13 30
39 18  5  4  3 12 29
40 19  6  1  2 11 28
41 20  7  8  9 10 27
42 21 22 23 24 25 26
43 44 45 46 47 48 49

It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8/13 ~ 62%.
If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed. If this process is continued, what is the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10%?
*/

/*
From q28:
For each ith ring, where 1st ring is 1 and 3rd ring is from 2 to 9, (i is odd)
The top right number is i^2, bottom left number is (i-1)^2 +1 = i^2 - 2i + 2
Top left number is i^2 - (i-1) = i^2 - i + 1
Top right number is (i-1)^2 + 1 - (i - 1) = i^2 - 3i + 3

At the ith ring, there are a total of 2i - 1 numbers on the diagonals.
We know i^2 will never be prime so we do not need to check that row.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPrime(int n) {
    if ((n & 1) == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if ((n % i) == 0) return false; 
    }
    return true;
}


int main() {
    int p = 0;
    for (int i = 3; i < INT_MAX; i += 2) {
        if (isPrime(i * i - 2 * i + 2)) p++;
        if (isPrime(i * i - i + 1)) p++;
        if (isPrime(i * i - 3 * i + 3)) p++;
        if ((10 * p) < (2 * i - 1)) {
            printf("%d\n", i); break;
        }
    }
    return 0;
}