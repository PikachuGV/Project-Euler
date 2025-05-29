/*
Consider the fraction, n/d, where n and d are positive integers. If n < d and HCF(n,d)=1, it is called a reduced proper fraction.
If we list the set of reduced proper fractions for d < 8 in ascending order of size, we get:
1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8

It can be seen that there are 3 fractions between 1/3 and 1/2.
How many fractions lie between 1/3 and 1/2 in the sorted set of reduced proper fractions for d<=12000?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int D = 12000;

const int un = 1, ud = 2;
const int ln = 1, ld = 3;

int isCoPrime(int a, int b) {
    //Binary GCD Algorithm
    
    if ((a&1)==0 && (b&1)==0) return 0;

    while ((a&1)==0) a>>=1;
    while ((b&1)==0) b>>=1;

    if (a==b) return a==1 ? 1 : 0;
    return (a>b) ? isCoPrime(a-b, b) : isCoPrime(a, b-a);
}

int main() {
    int n, c = 0;
    for (int d = 2; d <= D; d++) {
        //ln/ld < n/d < un/ud ==> n * td < d * tn and ln * d < n * ld
        for (int n = d * un / ud; n * ld > d * ln; n--) {
            if (n == un && d == ud) continue;
            if (n == ln && d == ld) continue;
            if (!isCoPrime(n, d)) continue; 
            c++;
        }
    }

    printf("%d\n", c);
    return 0;
}