/*
By listing the first six prime numbers: 2, 3, 5, 7, 11 and 13, we can see that the 6th prime is 13.
What is the 10001st prime number?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int* sieve(int n) {
    bool primes[n + 1];
    int c = n - 1;
    memset(primes, true, sizeof(primes));
    for (int i = 2; i * i <= n; i++) {
        if (primes[i]) {
            for (int j = i * i; j <= n; j += i) {
                if (primes[j]) c--;
                primes[j] = false;
            }
        }
    }

    int* allprimes = (int*)malloc((c + 1) * sizeof(int)); allprimes[c] = -1;

    int index = 0;
    for (int i = 2; i < n; i++) {
        if (primes[i]) {
            allprimes[index] = i; index++;
        }
    }

    return allprimes;
}

int main() {
    int n = 10001;
    int* primes = sieve(n * 100);
    printf("%d\n", primes[n - 1]);
    return 0;
}