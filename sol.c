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
Lets consider a 3 bit palindrome. For example,101.
The neat part about binary is that there exists the xor function. If two inputs are equal, the xor function outputs 0. This could help with palindromes.
Since we know 101 is 3 bits, we will take the most significant 2 bits of the number aka 10. (This can be done easily by doing 101>>(3/2)). Now we have to reverse the order of the bits such that the expected equal digits will line up. That can be done simply too, by doing 10 ^ 11 = 01. Now we get the least siginifacnt 2 bits of the number (Done by doing 101 && (1<<((3/2) +1) - 1)). Finally, we xor the 2 results and expect a result of 0 if the number is a palindromic number in base 2.
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
        store = malloc(power(10, (d+1)/2));
        currref = d % 2 == 0 ? ref2 : ref1;
        c=0;
        for (int j = 0; j < power(10, (d+1)/2); j++) {
            n = currref[j];
            for (int k = 0; k < 10; k++) {
                (*arr)[i] = k*power(10, d-1) + 10*n + k;
                store[c] = (*arr)[i];
                i++;c++;
            }
        }

        if (d%2==0) {
            free(ref2); 
            ref2 = malloc(power(10, (d+1)/2) * sizeof(int));
            memcpy(ref2, store, sizeof(int) * power(10, (d+1)/2));
        } else {
            free(ref1); 
            ref1 = malloc(power(10, (d+1)/2) * sizeof(int));
            memcpy(ref1, store, sizeof(int) * power(10, (d+1)/2));
        }
        free(store);
    }
    
}

int main() {
    int D = 6;
    int *palindromes, size;
    size = D % 2 == 0 ? 20/9 * (power(10,D/2) - 1) : 11/9 * (power(10, (D+1)/2)) - 20/9;
    palindromes = malloc(size * sizeof(int));

    genPalindromes(D, &palindromes);

    for (int i = 0; i<size; i++) printf("%d\n", palindromes[i]);

    return 0;
}