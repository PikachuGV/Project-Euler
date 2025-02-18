/*
The decimal expansion of the square root of two is 1.4142135623730...
If we define S(n, d) to be the the sum of the first d digits in the fractional part of the decimal expansion of sqrt(n), it can be seen that S(2, 10) = 4 + 1 + 4 + ... + 3 = 31.

It can be confirmed that S(2, 100) = 481.

Find S(13, 1000).

Note: Instead of just using arbitrary precision floats, try to be creative with your method.
*/

/*
We can do a binary search to search for each digit.
For example, we know that 3 < sqrt13 < 4. Let d be the first digit of the fractional part of sqrt13.
Guessing d = 5, we can see that 3.5 * 3.5 = 12.25 < 13. So we know that sqrt13 > 3.5
Now lets guess d = 7. We can see that 3.7 * 3.7 = 13.69 > 13. So we know sqrt13 < 3.7
Finally guess d = 6. We can see that 3.6 * 3.6 = 12.96 < 13. Thus 3.6 < sqrt13 < 3.7. This means d = 6.

The neat part is that we only have 10 possible digits to play around with. So it should be fine to do a simple linear search. d will be the largest digit that results in the square being less than 13.

Now we have to deal with multiplication here. Notice that no matter what the fractional part is, since we know that we are always getting closer and closer to n^2 = 13, we can safely assume that n^2 is always a 2 digit integer + decimals. So the first 2 digit of our result would be the integer part of n^2.
Hence we can treat the multiplication like a multiplication for normal integers, only caring about the first 2 digits of the result.

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

const int TENS[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int ndigits(int n) {
    if (n < 0) n *= -1;
    if (n == 0) return 1;
    for (int i = 1; i < 10; i++) {
        if (n < TENS[i]) return i;
    }
    
    exit(1000);
}

//NOTE: in both add and mul, the digits are placed in reverse order: last digit is the first element. If a and b have different number of digits, a will be the one with more digits. Pointer c is malloced before being passed.

void add(short *a, short *b, short **c, short lena, short lenb, short *lenc) {
    if (lena < lenb) exit(100);
    if (lena > lenb) {
        b = realloc(b, lena * sizeof(short));
        for (int i = lenb; i < lena; i++) b[i] = 0;
        lenb = lena;
    }
    (*lenc) = lena;
    free(*c); *c = calloc(*lenc, sizeof(short));
    short t, carry = 0;
    for (int i = 0; i < lena; i++) {
        t = a[i] + b[i] + carry;
        (*c)[i] = t % 10;
        carry = t / 10;
    }

    if (carry != 0) {
        (*lenc)++;
        (*c) = realloc(*c, (*lenc) * sizeof(short));
        (*c)[(*lenc) - 1] = carry;
    }
}

void mul(short *a, short *b, short **c, short lena, short lenb, short *lenc) {
    (*lenc) = lena + lenb - 1;
    free(*c); *c = calloc(*lenc, sizeof(short));

    short t, carry = 0, *C = calloc(*lenc, sizeof(short)), *T = calloc(*lenc, sizeof(short));
    
    for (int i = 0; i < lenb; i++) {
        memset(C, 0, *lenc * sizeof(short));
        for (int j = 0; j < lena; j++) {
            t = a[j] * b[i] + carry;
            C[i + j] = t % 10; carry = t / 10;
        }
        if (carry != 0) {
            if (i != lenb - 1) {
                C[i + lena] = carry;
            } else {
                (*lenc)++;
                C = realloc(C, (*lenc) * sizeof(short));
                (*c) = realloc((*c), (*lenc) * sizeof(short));
                T = realloc(T, (*lenc) * sizeof(short));
                C[(*lenc) - 1] = carry; (*c)[(*lenc) - 1] = 0;
            }
        }
        memcpy(T, *c, (*lenc) * sizeof(short));
        add(C, T, c, *lenc, *lenc, lenc);
    }

}

int main() {
    clock_t start = clock();
    short *n = calloc(1001, sizeof(int)), *t = malloc(0), lent, l = 1001;
    int s = 0;
    n[l - 1] = 3; 
    for (int i = 0; i < 1000; i++) {
        for (int d = 1; d < 10; d++) {
            n[l - 2 - i] = d;
            mul(n, n, &t, l, l, &lent);
            if (t[lent - 1] == 1 && t[lent - 2] == 3) {
                n[l - 2 - i] = d - 1; break;
            }
            s += n[l - 2 - i];
        }
    }

    printf("%d\n", s);
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime taken: %lf\n", time);
    return 0;
}