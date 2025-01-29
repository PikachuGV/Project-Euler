/*
If p is the perimeter of a right angle triangle with integral length sides, {a, b, c}, there are exactly three solutions for p = 120.
{20,48,52}, {24,45,51}, {30,40,50}
For which value of p <= 1000, is the number of solutions maximised?
*/

/*
This question is mainly asking us to find Pythogorean Triplets and then finding the sum of these triplets.

Euclid formula can help us find primitive Pythogarean Triplets quickly.

If we have integers m, n such that m and n are coprime and only one of them is even, then:
a = m^2 - n^2, b = 2mn, c = m^2 + n^2 will form a (a,b,c) primitive triplet.

Notice we want a + b + c <= 1000
So we have 2m^2 + 2mn <= 1000
m(m+n)<=500

Since m and m+n are both integers, we thus know that m+n<sqrt(500) ~ 22 so n < 22

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int gcd(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}

int main() {
    int sum[1001], a, b, c, max, maxp;
    memset(sum, 0, sizeof(sum));
    max = 0;

    for (int n = 1; n < 22; n++) {
        for (int m = n + 1; m * (m + n) <= 500; m += 2) {
            a = m * m - n * n; b = 2 * m * n; c = m * m + n * n;
            if (a * a + b * b == c * c) {
                if (a + b + c <= 1000) {
                    for (int i = 1; (a + b + c) * i <= 1000; i++) {
                        sum[(a + b + c) * i]++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 1000; i++) {
        if (sum[i] > max) {
            max = sum[i];
            maxp = i;
        }
    }

    printf("%d\n", maxp);

    return 0;
}