/*
The proper divisors of a number are all the divisors excluding the number itself. For example, the proper divisors of 28 are 1, 2, 4, 7, and 14. As the sum of these divisors is equal to 28, we call it a perfect number.
Interestingly the sum of the proper divisors of 220 is 284 and the sum of the proper divisors of 284 is 220, forming a chain of two numbers. For this reason, 220 and 284 are called an amicable pair.
Perhaps less well known are longer chains. For example, starting with 12496, we form a chain of five numbers:
12496 -> 14288 -> 15472 -> 14536 -> 14264 (-> 12496 -> ...)
Since this chain returns to its starting point, it is called an amicable chain.
Find the smallest member of the longest amicable chain with no element exceeding one million.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>

#define N 1000000

typedef struct n {
    int val;
    struct n *next;
    int seen;
    int head;
} NODE;

int sumdiv(int n) {
    int sum=0;

    for (int d = 1; d*d <= n; d++) {
        if ((n % d) == 0) {
            sum += (d + n/d);
        }
    }

    return sum-n;
}

int search(NODE *n, NODE **arr, int depth) {
    
    if (n->val == 0) return 0;
    if (n->head == 1) return depth;
    if (n->seen == 1) return 0;
    
    if (depth == 1) n->head = 1;
    n->seen = 1;

    int chain, idx;
    if (n->next == NULL) {
        idx = sumdiv(n->val);
        if (idx > N) {
            n->next = arr[0];
            return 0;
        }
        n->next = arr[idx];
    }
    
    chain = search(n->next, arr, depth+1);
    n->seen = 0;
    n->head = 0;
    return chain;
}

int main() {
    NODE *n;
    NODE **arr = calloc(N+1, sizeof(NODE*));
    for (int i = 0; i <= N; i++) {
        n = malloc(sizeof(NODE));
        n->val = i; n->next = NULL; n->seen = 0; n->head = 0;
        arr[i] = n;
    }


    int maxl = 0, l; NODE *start;
    
    for (int i = 1; i <= N; i++) {
        l = search(arr[i], arr, 1);
        if (l > maxl) {
            maxl = l; start = arr[i];
        }
    }

    n = start;
    while (n->seen == 0) {
        printf("%d ", n->val); n->seen = 1; n = n->next;
    }

    return 0;
}