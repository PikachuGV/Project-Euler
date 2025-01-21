/*
Q14: The following iterative sequence is defined for the set of positive integers:
n -> n/2 (n is even)
n -> 3n + 1 (n is odd)
Using the rule above and starting with 13, we generate the following sequence:
13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1.
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
Which starting number, under one million, produces the longest chain?
NOTE: Once the chain starts the terms are allowed to go above one million.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int chainlen, longeststart, longestchain = 0;

    short table[999999];
    memset(table, 0, sizeof(table));

    long long n;


    for (int i = 113383; i < 1000000; i++) {
        n = (long long)i;
        chainlen = 1;
        while (n != 1) {
            n = (n % 2 == 0) ? n / 2 : 3 * n + 1; 
            if (n < (long long)i) {
                chainlen += table[n]; break;
            }
            chainlen++;
        }
        if (chainlen > longestchain) {
            longestchain = chainlen;
            longeststart = i;
        }

        table[i] = chainlen;
    }

    printf("%ld\n", longeststart);

    return 0;
}