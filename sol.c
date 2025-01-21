/*
Q2: Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and , 2 the first terms will be:

1, 2, 3, 5, 8, 13, 21, 34, 55, 89,...
 
By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int a = 1, b = 2, c = 3, value = 2;

    while (c < 4000000) {
        if (c % 2 == 0) value += c;
        a = b; b = c; c = a + b;
    }

    printf("%d\n", value);
    
    return 0;
}