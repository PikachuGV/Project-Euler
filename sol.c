/*
It is easily proved that no equilateral triangle exists with integral length sides and integral area. However, the almost equilateral triangle 5-5-6 has an area of 12 square units.
We shall define an almost equilateral triangle to be a triangle for which two sides are equal and the third differs by no more than one unit.
Find the sum of the perimeters of all almost equilateral triangles with integral side lengths and area and whose perimeters do not exceed one billion (1,000,000,000).
*/

/*
For our scenario: a=b

Area of triangle = 1/2 absin@ = 1/2 a^2 sin@

We also know cos@ = (a^2 + b^2 - c^2)/2ab = (2a^2 - c^2)/2a^2
So sin@ = sqrt(4a^4 - (2a^2 - c^2)^2)/2a^2

= sqrt(4a^4 - 4a^4 + 4a^2 c^2 - c^4)/2a^2

= sqrt(4a^2 c^2 - c^4)/2a^2

= c sqrt(4a^2 - c^2)/2a^2


Thus area of triangle is 1/2 a^2 (c sqrt(4a^2 - c^2)/2a^2)
= 1/4 c sqrt(4a^2 - c^2);

If c = 0 mod 2, then sqrt(4a^2 - c^2) = 0 mod 2. This means c sqrt(4a^2 - c^2) = 0 mod 4.
If c = 1 mod 2, then c^2 = 1 mod 2 -> 4a^2 - c^2 = 1 mod 2. So sqrt(4a^2 - c^2) = 1 mod 2 and c sqrt(4a^2 - c^2) = 0 mod 4.

Hence c must be even for area to be integer.

A=mn, B=(m^2 - n^2)/2, C=(m^2 + n^2)/2 where m,n are coprime integers and m > n and both m and n are odd, form a primitive pythagoren triplet.

Notice that we have 4a^2 = (2a)^2. So we essentially need C = 2a and either A or B = c.
This actually means that no primitive pytagorean triplet will work since C will always be odd.
Thus we can actually find ANY primitive pythagorean triplet to start with, and we only consider the even multiples of these triplets. For each triplet multiple, there are 2 possibilites for c since both A and B will be even due to the multiplicative factor being even.

We want a+b+c = 2a+c <= 1 000 000 000.
So we have k(m^2 + n^2)/2 + min(kmn, k(m^2 - n^2)/2) <= 1 000 000 000
If kmn is min, then we have k(m+n)^2/2 <= 1 000 000 000 and hence sqrt(k)(m+n) <= 10000sqrt(10)
If k(m^2 - n^2)/2 is min, then we have km^2 <= 1 000 000 000 so sqrt(k)m <= 10000sqrt(10)

Notice this actually means that the perimeter of the almost equilateral triangle will be either (m+n)^2 or m^2.

We also need to make sure c = a+-1. a=k(m^2 + n^2)/4 and c=kmn or c=k(m^2 - n^2)/2.
If c=k(m^2 - n^2)/2, then a-c = k/4 ((m^2 + n^2) - 2(m^2 - n^2)) = k/4 (n^2 - m^2) < 0 since m>n.
If c=kmn, then a-c = k/4 (m^2 + n^2 - 4mn) = k/4 ((m-n)^2 - 2mn).
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

#define N 1000000000
#define max(a,b) ((a>b) ? a : b)
#define min(a,b) ((a<b) ? a : b)
typedef unsigned long long ULL;

ULL isCoPrime(ULL a, ULL b) {
    //Binary GCD Algorithm
    
    if ((a&1ULL)==0 && (b&1ULL)==0) return 0ULL;

    while ((a&1ULL)==0) a>>=1ULL;
    while ((b&1ULL)==0) b>>=1ULL;

    if (a==b) return a==1ULL ? 1ULL : 0ULL;
    return (a>b) ? isCoPrime(a-b, b) : isCoPrime(a, b-a);
}


int main() {
    double start = get_time();
    ULL sum = 0ULL, msq, maddnsq, msubnsq, mn, nsq, c, a, diff;
    for (ULL m = 3; m*m <= N; m+=2) {
        msq = m*m;
        for (ULL n = 1; n < m; n+=2) {
            if (!isCoPrime(m,n)) continue;
            nsq = n*n;
            mn = m*n;
            maddnsq = (m+n)*(m+n);
            msubnsq = (m-n)*(m-n);
            for (int k = 2; min(k*msq, k*maddnsq/2) <= N; k+=2) {
                if (k*msq <= N) {
                    diff = (3*nsq > msq) ? k*(3*nsq - msq)/4 : k*(msq - 3*nsq)/4;
                    if (diff == 1ULL) {
                        printf("%d, %d\n", k*(msq - nsq)/2, k*(msq + nsq)/4);
                        fflush(stdout);
                        sum += k*msq;
                    }
                }
                if (k*maddnsq/2 <= N) {
                    diff = (msubnsq > 2*mn) ? k*(msubnsq-2*mn)/4 : k*(2*mn-msubnsq)/4;
                    if(diff == 1ULL) {
                        printf("%d, %d\n", k*mn, k*(msq + nsq)/4);
                        fflush(stdout);
                        sum += k*maddnsq/2;
                    }
                };
                
            }
        }
    }

    printf("%llu\nTime taken: %lf", sum, get_time()-start);
    return 0;
}