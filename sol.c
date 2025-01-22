/*
The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
How many circular primes are there below one million?
*/

/*
Obviously we need to get all primes below 1000000.
We can ignore all primes that start with an even number since they will surely lead to a rotation that is even.
We can also ignore all primes that start with 5 since they will lead to a rotation ending in 5, which makes it divisible by 5.
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int sieve(int n, int **allprimes) {
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

    *allprimes = (int*)malloc(c * sizeof(int));

    int index = 0;
    for (int i = 2; i < n; i++) {
        if (primes[i]) {
            (*allprimes)[index] = i; index++;
        }
    }

    return c;
}

int power(int a, int b) {
    int c = 1;
    for (int i = 0; i < b; i++) {
        c *= a;
    }
    return c;
}

int digits(int n) {
    int c = 0;
    while (n != 0) {
        n /= 10; c++;
    }
    return c;
}

int search(int* arr, int n, int len) {
    if (len == 0) return -1;
    if (len == 1 && arr[0] != n) return -1;
    int mid = len / 2;

    if (arr[mid] == n) return mid;
    
    if (arr[mid] > n) {
        return search(arr, n, mid);
    } else {
        return search(&arr[mid + 1], n, len - mid - 1);
    }
}

int main() {
    int N, l, p, P, c, d, j, *primes;
    N = 1000000;
    l = sieve(N, &primes);
    c = 0;

    bool out;

    for (int i = 0; i < l; i++) {
        out = false;
        P = primes[i];
        if (P / 10 == 0) {
            c++; continue;
        }

        d = digits(P);
        p = 10 * P + (P / power(10, d - 1)) - ((P / power(10, d - 1)) * power(10, d)); 

        if (P == 79) {
            digits(1);
        }
        while (p != P) {
            if (search(primes, p, l) == -1) {
                out = true; break;
            }
            p = 10 * p + (p / power(10, d - 1)) - ((p / power(10, d - 1)) * power(10, d));
        }

        if (out == false) {
            c++;
        }

    }

    printf("%d\n", c);

    return 0;
}