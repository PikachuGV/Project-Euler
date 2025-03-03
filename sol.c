/*
If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
Not all numbers produce palindromes so quickly. For example,

349 + 943 = 1292
1292 + 2921 = 4213
4213 + 3124 = 7337

That is, 349 took three iterations to arrive at a palindrome.
Although no one has proved it yet, it is thought that some numbers, like 196, never produce a palindrome. A number that never forms a palindrome through the reverse and add process is called a Lychrel number. Due to the theoretical nature of these numbers, and for the purpose of this problem, we shall assume that a number is Lychrel until proven otherwise. In addition you are given that for every number below ten-thousand, it will either (i) become a palindrome in less than fifty iterations, or, (ii) no one, with all the computing power that exists, has managed so far to map it to a palindrome. In fact, 10677 is the first number to be shown to require over fifty iterations before producing a palindrome: 4668731596684224866951378664 (53 iterations, 28-digits).
Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.
How many Lychrel numbers are there below ten-thousand?
NOTE: Wording was modified slightly on 24 April 2007 to emphasise the theoretical nature of Lychrel numbers.
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int TENS[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};


char *add(char **a, char **b) {
    if (strlen(*a) != strlen(*b)) exit(10370);
    int len = strlen(*a);
    int digit = 0, carry = 0;
    
    char *c = calloc((len + 2), sizeof(char));
    
    for (int i = len - 1; i >= 0; i--) {
        digit = ((*a)[i] - '0') + ((*b)[i] - '0') + carry;
        carry = digit / 10;
        if (carry > 9 || carry < 0) {
        printf("%s, %s, %d", (*a), (*b), carry);
        exit(100);
        }
        c[i + 1] = (digit % 10) + '0';
    }
    if (carry != 0) {
        c[0] = carry + '0';
        return c;
    }
    return c + 1;
}

int ndigits(int n) {
    if (n < 0) n *= -1;
    if (n == 0) return 1;
    for (int i = 1; i < 10; i++) {
        if (n < TENS[i]) return i;
    }

    exit(1000);
}



bool isPalindromic(char* str) {
    int len = strlen(str);
    if (len == 1 || len == 0) return true;
    
    if (str[0] != str[len - 1]) return false;
    char new[(len - 2)];
    strncpy(new, str + 1, len - 2);
    new[len - 2] = '\0';
    bool result = isPalindromic(new);
    return result;
}

char *revstr(char *str) {
    int l = strlen(str);
    
    char *rev = calloc(l + 1, sizeof(char));
    for (int i = 0; i < l; i++) {
        rev[i] = (char)str[l - 1 - i];
    }
    return rev;
}


int main() {
    int N = 10000, d = 0, j, l = 0;
    char *str = malloc(0), *rev, *temp;

    for (int n = 1; n <= N; n++) {
        free(str);
        d = ndigits(n);
        str = calloc(d + 1, sizeof(char));
        sprintf(str, "%d", n);
        
        for (j = 0; j < 50; j++) {
            rev = revstr(str);
            temp = add(&str, &rev);
            free(str); free(rev);
            
            str = malloc(strlen(temp) * sizeof(char));
            memcpy(str, temp, strlen(temp) * sizeof(char));
            
            if (d == strlen(temp)) {
                free(temp - 1);
            } else {
                free(temp); d++;
            }
            
            if (isPalindromic(str)) break;
        }
        
        if (j == 50) l++;
    }
    
    printf("%d\n", l);
    return 0;
}
