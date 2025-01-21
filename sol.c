/*
Q10: The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
Find the sum of all the primes below two million.
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
    int n = 2000000; long long sum = 0;
    int* primes = sieve(n);
    for (int i = 0; primes[i] != -1; i++) {
        sum += (long long)primes[i];
    }

    printf("%lld\n", sum);

    return 0;
}