/*
It turns out that 12 cm is the smallest length of wire that can be bent to form an integer sided right angle triangle in exactly one way, but there are many more examples.

12 cm: (3,4,5)
24 cm: (6,8,10)
30 cm: (5,12,13)
36 cm: (9,12,15)
40 cm: (8,15,17)
48 cm: (12,16,20)

In contrast, some lengths of wire, like 20 cm, cannot be bent to form an integer sided right angle triangle, and other lengths allow more than one solution to be found; for example, using 120 cm it is possible to form exactly three different integer sided right angle triangles.

120 cm: (30,40,50), (20,48,52), (24,45,51)

Given that L is the length of the wire, for how many values of L < 1,500,000 can exactly one integer sided right angle triangle be formed?
*/

/*
For integers m, n such that m,n are coprime and both m and n are odd, then
a = mn, b = (m^2 - n^2)/2, c = (m^2 + n^2)/2 form all primitive Pythagorean triplets.

We want a+b+c<=L ==> m(m+n)<=L. We can thus safely say that m < sqrt(L)
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int L = 1500000;

int isCoPrime(int a, int b) {
    //Binary GCD Algorithm
    
    if ((a&1)==0 && (b&1)==0) return 0;

    while ((a&1)==0) a>>=1;
    while ((b&1)==0) b>>=1;

    if (a==b) return a==1 ? 1 : 0;
    return (a>b) ? isCoPrime(a-b, b) : isCoPrime(a, b-a);
}

int main() {
    int *l = calloc((L+1), sizeof(int));

    int a,b,c;
    for (int m=3; m*m < L; m+=2) {
        for (int n=1; n < m; n+=2) {
            if (m*(m+n)>L) break;
            if (!isCoPrime(m,n)) continue;
            
            a=m*n; b=(m*m - n*n)>>1; c=(m*m + n*n)>>1;

            for (int k = 1; k*(a+b+c)<=L; k++) l[k*(a+b+c)]++;
        }
    }

    int C = 0;
    for (int i = 0; i < L; i++) {
        if (l[i] == 1) C++; 
    }

    printf("%d\n", C);


    return 0;
}