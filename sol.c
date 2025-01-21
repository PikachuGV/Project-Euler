/*
Q17: If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int tens[] = {0, 0, 6, 6, 5, 5, 5, 7, 6, 6};
int digits[] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4};
int teen[] = {3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
//hundred = 7. hundreds have a and IF its not a full 

int lettersbelowhundred(int n) {
    if (n < 10) {
        return digits[n % 10];
    } else if (n < 20) {
        return teen[n % 10];
    } else if (n < 100) {
        return tens[n / 10] + digits[n % 10];
    }
}

int main() {
    int total = 0;

    for (int i = 1; i <= 1000; i++) {
        if (i % 100 == 0) {
            if (i != 1000) {
                total += digits[i / 100] + 7;
            } else {
                total += 11;
            }
        } else if (i > 100) {
            total += digits[i / 100] + 7 + 3 + lettersbelowhundred(i % 100);
        } else {
            total += lettersbelowhundred(i);
        }
    }

    printf("%d\n", total);

    return 0;
}