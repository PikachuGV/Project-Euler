/*
Q36: The decimal number, 585 = 1001001001 base 2 (binary), is palindromic in both bases.
Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
(Please note that the palindromic number, in either base, may not include leading zeros.)
*/

/*
Lets consider base 10 first and ignore the leading 0s restriction.

Lets start with a 1-digit long palindrome. The only possible ones are 0, 1, 2 ... 9 (obviously).
Now 2-digit long palindromes can be 00, 11, 22, ... 99
Now 3-digit long palindromes can be created by looking at the 1-digit long palindromes and appending a single digit to the front and back of it. The 3-digit long palindromes are thus 000, 101, 202,...,909, 010, 111...,919,...,999.
4-digit long palindromes can be created, similiarly, by appending to the 2-digit long palindromes. The possible 4 digit long palindromes are thus 0000, 1001, 2002,...,9009,0110,1111,...,9119,...,9999.

Notice that there are 10 1-digit long palindromes, 10 2-digit long palindromes, 10*10=100 3 digit palindromes and so on. Thus, for all palindromes with a max of n digits:
-If n is even, there are 2*(10+100+...+10^(n/2)) = 20/9 * (10^(n/2) - 1) palindromes.
-If n is odd, there are 2*(10+100+..+10^((n-1)/2)) + 10^((n+1)/2) = 20/9 * (10^((n-1)/2) - 1) + 10^((n+1)/2)
                                                                  = 11/9 * (10^((n+1)/2))  - 20/9

As such, we will produce every single palindrome possible, including the ones with leading 0s. To test whether a palindrome has leading 0s is simple: we just need to check whether its last digit is 0.

Now lets look at the base 2 palindromes.
We can reverse it quickly and check whether it is the same as the original.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int power(int a, int b) {
    int c = 1;
    for (int i = 0; i < b; i++) {
        c *= a;
    }
    return c;
}

void genPalindromes(int D, int **arr) {
    int i, n, c;

    int *ref1, *ref2, *store, *currref;

    ref1 = malloc(10 * sizeof(int)); //for odd digits
    ref2 = malloc(10 * sizeof(int)); //for even digits
    store = malloc(100 * sizeof(int)); //for current digit count

    for (i = 0; i < 10; i++) {
        (*arr)[i] = i;
        ref1[i] = i;
    }
    for (i = 10; i < 20; i++) {
        (*arr)[i] = 11*(i-10);
        ref2[i-10] = 11*(i-10);
    }

    for (int d = 3; d <= D; d++) {
        store = malloc(power(10, (d+1)/2) * sizeof(int));
        c=0;
        for (int j = 0; j < power(10, (d-1)/2); j++) {
            n = (d % 2 == 0) ? ref2[j] : ref1[j];

            for (int k = 0; k < 10; k++) {
                (*arr)[i] = k*power(10, d-1) + 10*n + k;
                store[c] = (*arr)[i];
                i++;c++;
            }
        }

        if (d%2==0) {
            free(ref2); 
            ref2 = malloc(power(10, d/2) * sizeof(int));
            memcpy(ref2, store, sizeof(int) * power(10, d/2));
        } else {
            free(ref1); 
            ref1 = malloc(power(10, d/2 + 1) * sizeof(int));
            memcpy(ref1, store, sizeof(int) * power(10, (d+1)/2));
        }
        free(store);
    }
    
}

int nbits(int n) {
    int i = 0;
    while (n != 0) {
        n >>= 1; i++;
    }
    return i;
}

bool isBinaryPalindrome(int n) {
    int rev = 0, m = n;
    while (m != 0) {
        rev <<= 1;
        rev |= m & 1;
        m >>= 1;
    }   
    return (bool)(rev==n);

}

int main() {
    clock_t start = clock();
    int D = 6;
    int *palindromes, size, c;
    size = D % 2 == 0 ? 20 * (power(10,D/2) - 1) / 9 : (11 * (power(10, (D+1)/2)) - 20) / 9;
    palindromes = malloc(size * sizeof(int));

    genPalindromes(D, &palindromes);

    c=0;

    for (int i = 0; i < size; i++) {
        if (palindromes[i] % 10 == 0) continue;
        if (isBinaryPalindrome(palindromes[i])) {
            c+=palindromes[i];
        }
    } 
    printf("%d\n", c);

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%lf\n", time);

    return 0;
}