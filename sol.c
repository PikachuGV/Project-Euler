/*
It is possible to write five as a sum in exactly six different ways:

4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1

How many different ways can one hundred be written as a sum of at least two positive integers?
*/

/*
Lets look at a simplier problem: write 5 as a sum of at least 2 positive integers.

5 = 1 + 1 + 1 + 1 + 1

We first start by using a 4. This leaves us with 1 and we cannot go further. Thus 5=4+1 is 1 way.

Then we use a 3, leaving us with a 2. 2 can be rewritten as 1+1 or left as 2. Thus there are 2 ways here.

We now use a 2 leaving us with a 3. Since 3>2 we cannot use 3 and must split it up. 3 can be split up using a 2 or 1. Using 2 leaves us with 1; using 1 leaves us with 2, which must be split up since 2>1. 2 can be split up into 1+1 which is valid. Thus there are 2 ways here.

Finally, we use a 1, leaving 4. 4 cannot be used, so we have to split it. Splitting using 3 or 2 isnt allowed since 3,2 > 1. So we can only use 1 to split leaving 3. Similar logics shows that only 1s can be used here, giving us 1 way.

Thus total = 1+2+2+1=6.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


const int N = 100;

int search(int n, int used) {
    if (n == 1) return 0;

    int d, ways = 0;
    for (int i = n-1; i>0; i--) {
        if (i>used) continue;
        d = n-i;
        //printf("%d, %d, %d\n", i, d, used);
        if (d<=i) ways++;

        ways += search(d, i);
    }

    return ways;
}

int main() {
    printf("%d\n", search(N,INT_MAX));
    return 0;
}