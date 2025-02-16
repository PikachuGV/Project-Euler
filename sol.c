/*
There are exactly ten ways of selecting three from five, 12345:
123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
In combinatorics, we use the notation, 5C3 = 10.
In general, nCr = n!/(r!(n-r)!), where r < n, n! = n * (n-1) * ... * 3 * 2 * 1, and 0! = 1.

It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
How many, not necessarily distinct, values of nCr for 1 < n < 100, are greater than one-million?
*/

/*
One property of nCr is that nCr = nC(n-r). So for every n, if nC(n/2) <= 1000000, we know that there is no possible r for which nCr > 1000000. Likewise, if there exists a r, say R <= N/2, where nCR > 1000000, assuming this R is the smallest r that satisfies the inequality, then we know that nCr > 1000000 occurs when R <= r <= n-R, aka for n-2R + 1 values.

Notice that we can write nCr as (n * (n-1) * (n-2) * ... * (n-r+1))/(1 * 2 * 3 * ... * r).
This will be much easier to calculate.

It is given that n=23 is the first n where nCr > 1000000 has a solution, smallest of which is 23C10. This also means that 23C9 <= 1000000. We can calculate that 23C9 = 817190.

Now for any nCr, we know that nCr + nC(r-1) = (n+1)Cr. This is actually very helpful since this means that we can find nCr using recursion (nCr = (n-1)Cr + (n-1)C(r-1)).

So letting nCr = f(n, r), we have
f(n, r) = f(n-1, r-1) + f(n-1, r)
If r is fixed:
f(n, r) - f(1, r) = sum f(n-1, r-1) from n = 2 to n = n
f(n, r) = sum f(n-1, r-1) from n=2 to n=n

We know that when r = 0, f(n, 0) = 1 for all n > 0.
So we can find all nC1, nC2, nC3 and so on and forth.
In fact, we just need to check until we find the first r for which nCr first exceeds 1000000 for all 1 <= n <= 100. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void ncR(int R, int **arr) {
    //f(2,r) = f(1,r-1)
    int s = 0, t = (*arr)[0];
    for (int i = 1; i < 100; i++) {
        //n = i + 1
        //arr[n-1] = f(n-1, r-1)
        s += t;
        t = (*arr)[i];
        (*arr)[i] = s;
    }
    //f(1,r)
    (*arr)[0] = (R == 1) ? 1 : 0;
}

int main() {
    int N = 1000000, *arr = malloc(100 * sizeof(int)), *c = calloc(100, sizeof(int));
    bool done;
    for (int i = 0; i < 100; i++) {
        arr[i] = i+1;
        if (i+1 > N) c[i] = 1;
    }
    for (int r = 2; r <= 50; r++) {
        done = true;
        ncR(r, &arr);
        for (int n = 0; n < 100; n++) {
            if (arr[n] == 0 && c[n] == 0) c[n] = -1;
            if (arr[n] > N && c[n] == 0) c[n] = r;
            if (c[n] == 0) done = false;
        }
        if (done) break;
    }
    int sum = 0;
    for (int i = 0; i < 100; i++) {
        if (c[i] != -1) {
            //n - 2R + 1 = i + 1 - 2R + 1 = i + 2 - 2R
            sum += i + 2 - (2 * c[i]);
        }
    }

    printf("%d\n", sum);

    return 0;
}