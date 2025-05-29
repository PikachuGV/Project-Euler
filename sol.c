/*
The number 145 is well known for the property that the sum of the factorial of its digits is equal to 145:
1! + 4! + 5! = 1 + 24 + 120 = 145.
Perhaps less well known is 169, in that it produces the longest chain of numbers that link back to 169; it turns out that there are only three such loops that exist:

169 -> 363601 -> 1454 -> 169
871 -> 45361 -> 871
872 -> 45362 -> 872

It is not difficult to prove that EVERY starting number will eventually get stuck in a loop. For example,

69 -> 363600 -> 1454 -> 169 -> 363601 (-> 1454)
78 -> 45360 -> 871 -> 45361 (-> 871)
540 -> 145 (-> 145)

Starting with 69 produces a chain of five non-repeating terms, but the longest non-repeating chain with a starting number below one million is sixty terms.
How many chains, with a starting number below one million, contain exactly sixty non-repeating terms?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int *chains;

const int N = 1000000;
const int factorials[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880}; 

int factorialSum(int n) {
    int s = 0;
    while (n != 0) {
        s += factorials[n%10];
        n /= 10;
    }
    return s;
}

int search(int n) {
    if (chains[n] != 0) {
        return chains[n];
    } 

    int l = search(factorialSum(n)) + 1;
    chains[n] = l;
    return l;
}

int main() {
    chains = calloc(N+1 ,sizeof(int));
    chains[169] = 3; chains[871] = 2; chains[872] = 2; chains[1] = 1;
    chains[363601] = 3; chains[1454] = 3; chains[45362] = 2; chains[45361] = 2;
    
    
    for (int i = 1; i <= N; i++) search(i);
    for (int i = 1; i <= N; i++) {
        if (chains[i] == 60) printf("%d ", i);
    }


    return 0;
}