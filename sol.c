/*
Q34: 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
Find the sum of all numbers which are equal to the sum of the factorial of their digits.
Note: As 1! = 1 and 2! = 2 are not sums they are not included.
*/

/*
Notice 9! = 362880
9! + 9! = 725760
9! + 9! + 9! = 1,088,640
9! + 9! + 9! + 9! = 1,451,520
9! + 9! + 9! + 9! + 9! = 1,814,400
9! + 9! + 9! + 9! + 9! + 9! = 2,177,280
9! + 9! + 9! + 9! + 9! + 9! + 9! = 2,540,160
9! + 9! + 9! + 9! + 9! + 9! + 9! + 9!= 2,903,040
The maximum possible number of digits is thus 7. The minimum is 2.

List of factorials are as follows: 1 1 2 6 24 120 720 5040 40320 362880

Notice that the factorials 1 digit long are from 0! to 3!. 2 digit long contains only 4!. 3 digit long contains 5! and 6!. 4 digit long contains 7!, 5 digit long contains 8! and 6 digit long contains 9!.

This means for any N with n digits, for sum of factorial of its digits to be equal to itself, it cannot contain any digit that has a factorial with digit count > n.

Furthermore, lets consider 1234. Instead of calculating the sum by brute force, notice that we would have encountered the number 123 before this. Thus all we need to do is to add 4! to the sum for 123. Memorisation would work here, but the problem is that there are too many numbers.
Fortunately, we only need to remember the results for numbers 1 digit less than what we are at. So we can have 2 arrays, one for reference and one for storage of current results. When we reach n=10^i, then we can clear the reference array and store the results into the reference array. Clear the storage array too.
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

int main() {
    int factorials[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880}; 
    int avaliable[7] = {0, 4, 5, 7, 8, 9, 10}; //Avlaible number of factorials for i digits.
    int d, s, S, *ref, *store;

    ref = malloc(10 * sizeof(int)); memcpy(ref, &factorials, sizeof(factorials));
    store = malloc(91 * sizeof(int));

    d = 2; S = 0;
    for (int n = 11; n < power(10, 7); n++) {
        if (n == power(10, d)) {
            free(ref); 
            ref = malloc((power(10, d - 1) * 9 + 1) * sizeof(int));
            memcpy(ref, store, (power(10, d - 1) * 9 + 1) * sizeof(int));
            free(store);
            store = malloc((power(10, d) * 9 + 1) * sizeof(int));
            d++;
        }

        s = (d == 2) ? ref[(n / 10)] + factorials[n % 10] : ref[(n / 10) - power(10, d - 2)] + factorials[n % 10];

        store[n - power(10, d - 1)] = s;
        if (s == n) {
            S+=n;
        }
    }

    printf("%d\n", S);

    return 0;
}