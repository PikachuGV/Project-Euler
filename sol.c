/*
By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the ten generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.
*/

/*
Replacing the last digit will lead to a maximum of 4 possible primes (since numbers ending in 0, 2, 4, 5, 6, 8 are always composite). So we cannot change the last digit for our problem.

Since primes are not divisble by 3, we can use the fact that sum of digits divisible by 3 -> number divisible by 3 to help us with our work.
If p is the prime we are concerned about, then we know that sum of digits of p is also not divisble by 3. Hence it can only be either 1 or 2 mod 3.
Whichever the case is, changing only 1 digit will cause the new prime to eventually have its sum of digits to be divisble by 3. For example, lets take 17 as an example. Changing the first digit, we have 
17, 27, 37, 47, 57, 67, 77, 87, 97. Notice that since 1 + 7 = 8 = 2 mod 3, then increasing the first digit by 1 will lead to 2 + 7 = 9 = 0 mod 3. So when the first digit is 2, 5, 8, *7 is composite. In fact if we only change 1 digit, it will occur for 3 possible choices of digits. So we have to change more than 1 digit.

Changing 2 digits will cause the remainder to increase/decrease by 2 each time. So if we start with 1 mod 3, and assuming we are only increasing the digits, then we have 1->0->2->1->0->2->1->0->2->1. If we start with 2 mod 1 then we have 2->1->0->2->1->0->2->1->0->2. Whichever way we do it we also have 3 possible choices of digits for which the new number is divisble by 3. So we have to change more than 3 digits.

Now changing 3 digits will conserve the modulo of sum of digits. Thats because every increase or decrease will change the sum of digits by 3, effectively conserving the modulo. So the minimum number of digits we have to change is 3.

Notice for 4 and 5 digits, we change the sum by 4 or 5 every step respectively. In modulo 3, it is the same as changing the sum by 1 or 2 every step, which we have discussed above.

Hence we can deduce that we must change 3k digits. The minimum prime must thus be at least 1000.

For 4 digit numbers, we already established that we cannot change the last digit. This means we can only change the first 3 digits. Let the unique digit be a and the repeated digit be b. Then we know that when we set b = a, the new number formed is divisble by 1111. We also know that b != 0. The question now is whether all 9 of the remaining numbers are prime. Furthermore, since the sum of 3 identical digits is just 3 * digit, a cannot be either 3 or 9 since that makes bbba divisible by 3.
We can actually just check it by hand.
If a = 1, then 5551 is divisible by 7.
If a = 7, then 2227 is divisible by 17

So we need 5 digit numbers.



*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int TENS[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

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

int ndigits(int n) {
    for (int i = 0; i < 10; i++) {
        if (n < TENS[i]) return i;
    }
    exit(100);
}

int tsd(int n) {
    int c[10], d; memset(c, 0, sizeof(c));
    n /= 10;
    while (n != 0) {
        d = n % 10;
        c[d]++;
        if (c[d] == 3) return d; 
        n /= 10;
    }
    return -1;
}

int* replace(int n, int d) {
    int D = ndigits(n);
    int N[D], *P, I[3], j = 0;
    P = calloc(10, sizeof(int));
    for (int i = D - 1; i >= 0; i--) {
        N[i] = n % 10; n /= 10;
        if (N[i] == d && j < 3) {
            I[j] = i; j++;
        }
    }

    for (int i = 0; i < 10; i++) {
        for (j = 0; j < 3; j++) {
            N[I[j]] = i;
        }
        for (int r = 1; r <= D; r++) {
            P[i] += (TENS[r - 1] * N[D - r]);
        }
    }
    return P;
}

int main() {
    int *primes, c, *P, d, p, C;
    c = sieve(2, 1000000, &primes);
    for (int i = 0; i < c; i++) {
        p = primes[i]; d = tsd(primes[i]); C = 0;
        if (d != -1) {
            P = replace(primes[i], d);
            for (int i = 0; i < 10; i++) {
                if (search(primes, P[i], c)) C++;
            }
            if (C == 8) {
                for (int i = 0; i < 10; i++) {
                    if (search(primes, P[i], c)) printf("%d ", P[i]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}