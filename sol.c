/*
Q4: A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 * 99.
Find the largest palindrome made from the product of two 3-digit numbers. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define max(a, b) ((a > b) ? a : b)

bool isPalindromic(char* str) {
    int len = strlen(str);
    if (len == 1 || len == 0) return true;
    if (str[0] != str[len - 1]) return false;
    char* new = malloc(sizeof(char) * (len - 2));
    strncpy(new, str + 1, len - 2);
    new[len - 2] = '\0';
    return isPalindromic(new);
}

int main() {
    int biggest = 0;
    for (int a = 999; a > 0; a--) {
        for (int b = a; b <= 999; b++) {
            int prod = a * b;
            char* str = malloc((int)((ceil(log10(prod))+1)*sizeof(char)));
            sprintf(str, "%d", prod);
            if (isPalindromic(str)) {
                biggest = max(biggest, prod);
            }
        }
    }
    printf("%d\n", biggest);
    return 0;
}