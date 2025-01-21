/*
Q21: Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a =/= b, then a and b are an amicable pair and each of a and b are called amicable numbers.
For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
Evaluate the sum of all the amicable numbers under 10000.
*/

/*

15 = 3 * 5
sum of all divisors = 1 + 3 + 5 + 3 * 5 = (1 + 3) + 5 * (1 + 3) = (1+5)(1+3)
30 = 2 * 3 * 5
sum of all divisors = sum(2 * each divisor in 15 + each divisor in 15)
                    = (1+2)sum(each divisor in 15)
                    = (1+2)(1+3)(1+5)
60 = 2^2 * 3 * 5
sum of all divisors = sum(2^2 * each divisor in 15 + 2 * each divisor in 15 + each divisor in 15)
                    =(1+2+4)(1+3)(1+5)


sums = list(30000)
for 2 < i < 10000
    total = 1
    factor = 1
    c = 0
    n = i
    while n is even, n/=2, c++, factor += (1 << c)
    total*=factor

    for odd j in 2 < n <= sqrti
        factor = 1
        c = 0
        while n divisible by j, n/=j,c++,factor += j^c
        total*=factor
    if n != 1 total *= (1 + n)
    sums[total] += i

amicable = 0
for all nums in sums if len(sum) > 1 amicable += num in nums
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int power(int a, int b) {
    int c = 1;
    for (int i = 0; i < b; i++) {
        c *= a;
    }
    return c;
}

int sumpdiv(int n) {
    int total, factor, c, m;

    total = 1, factor = 1, c = 0, m = n; 
    while (n % 2 == 0) {
        n /= 2;
        c++;
        factor += (1 << c);
    }
    total *= factor;
    for (int j = 3; j * j <= n; j += 2) {
        factor = 1;
        c = 0;
        while (n % j == 0) {
            n/=j,
            c++,
            factor += power(j, c);
        }    
        total*=factor;
    }
    if (n != 1) total *= (1 + n);

    total -= m;

    return total;
}

int main() {
    sumpdiv(1210);
    int N = 10000;

    int answer = 0;
    for (int i = 2; i < N; i++) {
        int m = sumpdiv(i);
        if (i==1184) {
            printf("%d, %d\n", m, i);}
        sumpdiv(m);
        if (m < i && sumpdiv(m) == i) {
            answer += m + i;
        }
    }
    //for (int i = 0; i < N; i++) printf("%d ", sums[i]);
    //for (int i = 0; i < len; i++) printf("%d ", checkedsums[i]);
    printf("\n%d\n", answer);

    return 0;
}