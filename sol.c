/*
The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
*/

/*
No even numbers other than 2 can be used.
So we have 1 2 3 5 7 9 to play around with.
In fact 2 can only be the first digit. Anywhere else will lead to a even stage.
Same for 5. If its not the first digit then it will lead a stage ending with 5.
1 and 9 cannot be the first or last digit. Because 1 and 9 are not prime.
So we can essentially only play with 1,3 7 9 as the middle digits, and 3 7 as the last digit.

Notice if we only consider truncation from the left, then we can produce n-digit truncatable primes by appending any digit to the left of any (n-1)-digit truncatable prime and checking whether the number itself is prime. Same for right truncatable primes.
So we can produce all possible truncatable primes from one direction, and check which of them are also truncatable from the other direction. It all depends on which direction has the lesser primes.
Notice we are likely to check for more primes if we do it from the left at each iteration, since we can append any digit to the left of the primes. However, for right-truncatable primes, we cannot append 0, 5 or any even number as those will surely lead to a composite number. So it is likely to be better and faster if we try to find right-truncatable primes first.

Now to check whether a prime is left truncatable, we have also established that
-if 1 or 9 are present, they cannot be the last digit.
So when checking for which primes are left-truncatable, we can ignore all primes that end with 1 or 9.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPrime(int n) {
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    
    return true;
}

bool isLeftTruncatable(int n) {
    if (n % 10 == 1 || n % 10 == 9) return false;
    
    for (int d = digits(n) - 1; d > 0; d--) {
        n %= power(10, d);
        if (isPrime(n) == false) return false;
    }
    
    return true;
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

int main() {
    int sum, n, *primes, *ref, *store;
    int p, r, s;
    primes = malloc(4 * sizeof(int)); ref = malloc(4 * sizeof(int));
    p = 4; r = 4; sum = 0;
    primes[0] = 2; primes[1] = 3; primes[2] = 5; primes[3] = 7;
    memcpy(ref, primes, 4 * sizeof(int));
    
    for (int LOOP_COUNT = 0; LOOP_COUNT < 0xFFFFFFFF; LOOP_COUNT++) {
        store = malloc(r * 4 * sizeof(int)); s = 0;
        for (int i = 0; i < r; i++) {
            n = ref[i] * 10;
            for (int d = 1; d < 10; d += 2) {
                if (d == 5) continue;
                n += d;
                if (isPrime(n) == true) {
                    p++; s++;
                    primes = realloc(primes, p * sizeof(int));
                    primes[p - 1] = n; store[s - 1] = n;
                }
                n -= d;
            }
        }
        if (s == 0) break;
        free(ref); ref = malloc(s * sizeof(int));
        memcpy(ref, store, s * sizeof(int));
        free(store);
        r = s;
    }
    
    for (int i = 0; i < p; i++) {
        n = primes[i];
        if (n % 10 == 1 || n % 10 == 9) continue;
        if (isLeftTruncatable(n) == true && n >= 10) {sum += n; printf("%d\n", n);}
    }
    
    printf("%d\n", sum);
    
    
    return 0;
}
