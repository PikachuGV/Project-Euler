/*
The prime factors of 13195 are 5, 7, 13 and 29.
What is the largest prime factor of the number 600851475143? 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    long long n = 600851475143;
    while (n % 2 == 0) {
        n >>= 1;
    }

    for (int i = 3; i * i < n; i += 2) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
        }
    }

    int maxPrime = n == 1 ? 2 : n;
    printf("%d\n", maxPrime);
    return 0;
}