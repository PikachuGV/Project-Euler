/*
It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

9 = 7 + 2 * 1^2
15 = 7 + 2 * 2^2
21 = 3 + 2 * 3^2
25 = 7 + 2 * 3^2
27 = 19 + 2 * 2^2
33 = 31 + 2 * 1^2

It turns out that the conjecture was false.
What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void sieve(int n, bool **isPrime) {
    int c = n - 1;
    *isPrime = malloc((n + 1) * sizeof(bool));
    (*isPrime)[0] = false; (*isPrime)[1] = false;
    memset(*isPrime, true, (n + 1) * sizeof(bool));
    for (int i = 2; i * i <= n; i++) {
        if ((*isPrime)[i]) {
            for (int j = i * i; j <= n; j += i) {
                if ((*isPrime)[j]) c--;
                (*isPrime)[j] = false;
            }
        }
    }
}   

int main() {
    int N = 1000000;
    bool *primes, out;
    sieve(N, &primes);
    for (int i = 0; i <= N; i++) {
        out = false;
        if (primes[i] || i % 2 == 0) continue;
        for (int j = 0; 2 * j * j < i; j++) {
            if (primes[i - (2 *(j * j))] == true) {
                out = true; break;
            }
        }

        if (out == false) {
            printf("%d\n", i);
            break;
        } 
    }
    return 0;
}