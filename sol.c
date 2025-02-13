/*
The prime 41, can be written as the sum of six consecutive primes:
41 = 2 + 3 + 5 + 7 + 11 + 13.
This is the longest sum of consecutive primes that adds to a prime below one-hundred.
The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.
Which prime, below one-million, can be written as the sum of the most consecutive primes?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define max(a,b) ((a > b) ? a : b)

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

    //i represents the multiple that we are sieving out now. We only need to sieve until i = sqrt(end) since any number above sqrt(end) is either a prime or a multiple of some number below sqrt(end).
    for (int i = 2; i * i <= end; i++) {
        if (i > start && !primes[i - start]) continue;
        if (i * i < start) {
            //We set the start multiple to be start if start is already a multiple of i. Else we find the next multiple of i greater than start.
            s = (start % i == 0) ? start : (start / i + 1) * i;
        } else {
            //If i * i >= start then we have to start from i * i directly. 
            s = i * i;
        }
        //This loops through all multiples of i from start bound to end bound
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

int main() {
    int *primes, c, p, largest, len, N = 1000000;
    c = sieve(2, N, &primes);
    p = 0; largest = 0; len = 0;
    for (int i = 0; i < c; i++) {
        p = primes[i];
        if (p > N / 2) break;
        for (int j = i + 1; j < c; j++) {
            p += primes[j];
            if (p > N) break;
            if (search(primes, p, c) && ((j - i + 1) > len)) {
                largest = max(largest, p); len = j - i + 1;
            }
        }
    }
    printf("%d\n", largest);
    return 0;
}