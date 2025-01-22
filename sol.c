/*
Q33: The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.
We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.
If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
*/

/*
We dont have to check for all pairs of 2 digit numbers to find the answer.
Instead, we start with pairs of 1 digit numbers. The fraction that we will look at is a/b, where a and b are both 1 digit numbers and a < b.
Now we will append a digit to a. We only need to consider when the digit is appended to the end of a and when the digit is smaller than a. For example, for a=4, appending gives us 40, 41, 42, 43...,49. We dont need to consider cases where we append to the front eg 14, 24, 34, ...94, because these numbers will surely be considered for other values of a, eg a=1 will consider 14.

Now we will only append to the front for the denominator. It can be proven that the only way for this type of fraction to be "simplified" by cancelling the end digits of both the numerator and denominator is for either the end digit to be 0, or the numerator and denominator to be equal, both of which are ignored in our problem.

Proof:
Let a/b be the "simplified" fraction where a and b are both 1 digits. Let d be the digit appended to the end of a and b. What we want is 10a+d / 10b+d = a/b
Cross multiplying gives 10ab+bd = 10ab+ad -> ad = bd
So we have either d=0 or a=b. QED.s

As such, we will only append the digit to the front of b. Notice if we have a/b = x/y, then ay=bx. Checking for this equality will be much more accurate then checking for the equality of fractions.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define max(a, b) ((a > b) ? a : b)

int gcd(int a, int b) {
    int c = 1;
    for (int i = 2; i <= max(a/2, b/2); i++) {
        if (a % i == 0 && b % i == 0) {
            c = i;
        }
    }
    return c;
}

int main() {
    int a, b, x, y, d, num = 1, den = 1;
    for (a = 1; a < 10; a++) for (b = a+1; b < 10; b++) for (d = a; d < 10; d++) {
        x = 10 * a + d; y = 10 * d + b;
        if (a*y==b*x) {
            num *= x; den *= y;
        }
    }

    printf("%d, %d, %d\n", num, den, den / gcd(num, den));

    return 0;
}