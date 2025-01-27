/*
Take the number 192 and multiply it by each of 1, 2, and 3:

192 * 1 = 192
192 * 2 = 384
192 * 3 = 576

By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3).
The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).
What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2,..., n) where n > 1?
*/

/*
Notice that the number of digits of k play a part here. If k has d digits, then we know that 9k has at least d digits and at most d+1 digits.
1) If k is 1 digit, then we have n=9-i, 0<=i<=4. (k till (9-2i)k are 1 digits, (10-2i)k till 9k are 2 digits)

2) If k is 2 digit, then we must have n=4 (k till 3k are 2 digits, 4k is 3 digits)

3) If k is 3 digit, then we must have n=3 (k till 3k are all 3 digits)

4) If k is 4 digit, then we must have n=2 (k is 4 digit, 2k is 5 digit)

As mentioned the maximum number of digits is 4. So we only need to check from 1 to 9999.

9 digits means we can represent the presence of each digit with a 9-bit (2^9=512) number.

For each number:
We set the bits of each digit that appears. If the digit bit is set we skip this number and continue on.
We then get its 2nd multiple and do the same. Same for 3rd multiple, 4th multiple...until every single bit is set aka we get a value of 111111111. If that is the case then we return the concatenated product (can be gotten while doing the digit bit).

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define max(a,b) ((a > b) ? a : b)

int ndigits(int n) {
    int c = 0;
    while (n != 0) {
        n /= 10; c++;
    }
    return c;
}

int power(int a, int b) {
    int c = 1;
    for (int i = 0; i < b; i++) {
        c *= a;
    }
    return c;
}

int main() {
    int largest = 0, digits, prod, n, p;
    bool out;
    for (int i = 1; i < 10000; i++) {
        digits = 0; prod = 0; out = false;
        for (int j = 1; j < 0xFFFFFFF && digits != (1<<9) - 1; j++) {
            n = i * j;
            for (int d = ndigits(n) - 1; d >= 0; d--) {
                p = power(10, d);
                prod *= 10; prod += n / p;
                if (n/p == 0 || (digits & (1 << (n/p - 1))) != 0) {
                    out = true;
                    break;
                }
                digits |= (1 << (n/p - 1));
                n %= p;
            }
            
            if (out == true) {break;}
        }
        if (out == false) largest = max(prod, largest);
    }
    
    printf("%d\n", largest);
    return 0;
}
