/*
Q31: In the United Kingdom the currency is made up of pound (£) and pence (p). There are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p), and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int coins[] = {1, 2, 5, 10, 20, 50, 100, 200};

int ways(int n, int S) {
    int w = 0;
    if (S < 0) return 0;
    if (S == 0) return 1;
    if (n == 0) return 0;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = coins[i]; j <= S; j += coins[i]) {
            w += ways(i, S - j);
        }
    }

    return w;
}

int main() {
    int N = 200;
    printf("%d\n", ways(8, N));
    return 0;
}