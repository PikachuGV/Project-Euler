/*
The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.
There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.
What 12-digit number do you form by concatenating the three terms in this sequence?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool search(int* arr, int n, int len) {
    if (len == 0) return false;
    if (len == 1 && arr[0] != n) return false;
    int mid = len / 2;

    if (arr[mid] == n) return true;
    
    if (arr[mid] > n) {
        return search(arr, n, mid);
    } else {
        return search(&arr[mid + 1], n, len - mid - 1);
    }
}

int sieve(int start, int end, int **allprimes) {
    bool primes[end - start + 1];
    int c = end - start + 1, s;
    memset(primes, true, sizeof(primes));
    for (int i = 2; i * i <= end; i++) {
        if (i > start && !primes[i]) continue;
        if (i * i < start) {
            s = (start % i == 0) ? start : (start / i + 1) * i;
        } else {
            s = i * i;
        }
        for (int j = s; j <= end; j += i) {
            if (primes[j - start]) c--;
            primes[j - start] = false;
        }
    }

    *allprimes = (int*)malloc(c * sizeof(int));

    int index = 0;
    for (int i = start; i < end; i++) {
        if (primes[i - start]) {
            (*allprimes)[index] = i; index++;
        }
    }

    return c;
}

bool sameDigits(int a, int b) {
    int A[4], B[4];
    for (int i = 3; i >= 0; i--) {
        A[i] = a % 10; B[i] = b % 10;
        a /= 10; b /= 10;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (A[i] == B[j]) {B[j] = -1; break;}
        }
    }

    for (int i = 0; i < 4; i++) {
        if (B[i] != -1) return false;
    }
    return true;
}

int main() {
    int *primes, c, p;
    c = sieve(1000, 10000, &primes);
    for (int i = 0; i < c; i++) {
        p = primes[i];
        
        for (int j = i + 1; j < c; j++) {
            if (sameDigits(p,primes[j])&&sameDigits(p,2*primes[j]-p)&&search(primes,2*primes[j]-p,c)) {
                printf("%d, %d, %d\n", p, primes[j], 2*primes[j] - p);
            }
        }
    }
    

    return 0;
}