/*
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
What is the smallest positive number that is evenly divisible (divisible with no remainder) by all of the numbers from 1 to 20?
*/

/*
Think about 2520.
Obviously it is evenly divisible by 1.
We can check that it is evenly divisible by 2, 3, 5, 7.
Now that means that it is divisible by 6 since 6 = 2 * 3. Same for 10 = 5 * 2.
We cant be certain that it is divisible by 4 without checking since 4 = 2 * 2.
Same for 8 = 2 * 2 * 2 and 9 = 3 * 3
All of these mean that 2520 = 2 * 3 * 5 * 7 * 2 * 2 * 3.

Plan:
Get all primes in range.
For each prime, find its smallest power that in contained in range.
Product of smallest power gives smallest result.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
    int smallest = 1;
    for (int i = 0; i < 8; i++) {
        int prime = primes[i];
        int value = prime;
        while (value * prime < 20) {
            value *= prime;
        }
        smallest *= value;
    }

    printf("%d\n", smallest);
    return 0;
}