/*
A number chain is created by continuously adding the square of the digits in a number to form a new number until it has been seen before.
For example,

44 -> 32 -> 13 -> 10 -> 1 -> 1
85 -> 89 -> 145 -> 42 -> 20 -> 4 -> 16 -> 37 -> 58 -> 89

Therefore any chain that arrives at 1 or 89 will become stuck in an endless loop. What is most amazing is that EVERY starting number will eventually arrive at 1 or 89.
How many starting numbers below ten million will arrive at 89?
*/

/*
Obviously a brute force method is the simplest method to solve this. But because we are dealing with 10 million numbers, we have to be a little smart about how we do this.

Notice that for a n-digit number, the biggest possible sum of squared digits will be 81n.
This would mean that for the maximum of 10000000, we only need to consider 6 digits (since sum of squared digits for 10000000 is just 1.)
Biggest possible sum is 81*6 = 486.
So we only need to search up till 486 in order to solve the question. After which, every number can just be found via a lookup.
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N_DIGITS 7
#define MAX_ITER 1000

int sqdigits(int n) {
    int sum = 0;
    while (n != 0) {
        sum += (n%10)*(n%10);
        n /= 10;
    }

    return sum;
}

int main() {
    int table[N_DIGITS*81 + 1] = {0}, n, c1 = 0, c2 = 0;
    for (int i = 1; i <= N_DIGITS * 81; i++) {
        n = i;
        for (int j = 0; j < MAX_ITER; j++) {
            n = sqdigits(n);
            if (table[n] != 0) {
                table[i] = table[n];
                (table[n]==1) ? c1++ : c2++;
                break;
            }
            if (n == 1) {
                table[i] = 1; c1++; break;
            }
            if (n == 89) {
                table[i] = 89; c2++; break;
            }

            if (j == MAX_ITER - 1) exit(101010);
        }
    }

    for (int i = (N_DIGITS*81) + 1; i <= 10000000; i++) {
        if (table[sqdigits(i)] == 1) c1++;
        if (table[sqdigits(i)] == 89) c2++;
    }

    printf("%d, %d, %d", c1,c2,c1+c2);
    return 0;
}
