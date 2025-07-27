/*
For a number written in Roman numerals to be considered valid there are basic rules which must be followed. Even though the rules allow some numbers to be expressed in more than one way there is always a "best" way of writing a particular number.
For example, it would appear that there are at least six ways of writing the number sixteen:
IIIIIIIIIIIIIIII
VIIIIIIIIIII
VVIIIIII
XIIIIII
VVVI
XVI
However, according to the rules only XIIIIII and XVI are valid, and the last example is considered to be the most efficient, as it uses the least number of numerals.
The 11K text file, roman.txt, contains one thousand numbers written in valid, but not necessarily minimal, Roman numerals; see About... Roman Numerals for the definitive rules for this problem.
Find the number of characters saved by writing each of these in their minimal form.
Note: You can assume that all the Roman numerals in the file contain no more than four consecutive identical units.
*/

/*
We could just convert these roman numerals to integer form and convert them back.

To convert from roman numerals to integers:
    We go through each letter of the list and keep track of the previous denomination
    If the denomination either stays the same or decreases, we just add the value of the denomination.
    However, if there is an increase in denomination, it means to say that we have hit a subtractive form. Thus we would have to undo the addition done previously and instead do the value of the subtractive form.

To convert from integers to roman numerals:
    If integer >= 1000 then we use denomination M.
    If integer % 100 == 9 then we use CM.
    If integer % 100 == 5 then we use D.
    If integer % 100 == 4 then we use CD.
    If integer >= 100 then we use C.
    If integer % 10 == 9 then we use XC.
    If integer % 10 == 5 then we use L.
    If integer % 10 == 4 then we use XL.
    If integer >= 10 then we use X.
    If integer == 9 then we use IX.
    If integer == 5 then we use V.
    If integer == 4 then we use IV.
    Else we use I.

    If we are not using a subtractive form, then we add (integer/denomination) denominations.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef enum d {
    I = 1,
    IV = 4,
    V = 5,
    IX = 9,
    X = 10,
    XL = 40,
    L = 50,
    XC = 90,
    C = 100,
    CD = 400,
    D = 500,
    CM = 900,
    M = 1000
} DENOMINATIONS;

DENOMINATIONS getD(char c) {
    switch (c) {
        case 'I':
            return I;
        case 'V':
            return V;
        case 'X':
            return X;
        case 'L':
            return L;
        case 'C':
            return C;
        case 'D':
            return D;
        case 'M':
            return M;
    }
}

int rtoi(char *roman) {
    DENOMINATIONS prevd = M, d;
    int n = 0;
    for (int i = 0; i < strlen(roman); i++) {
        d = getD(roman[i]);
        if (d > prevd) {
            //Subtractive form hit.
            n -= prevd;
            n += (d - prevd);
        } else {
            n += d;
        }
        prevd = d;
    }

    return n;
}

char *itor(int n) {
    char *str = calloc(50,sizeof(char)); int i=0;
    int t;
    while (n > 0) {
        if (n >= M) {
            t = n/M;
            for (int c = 0; c < t; c++) {
                str[i] = 'M'; i++; n-=M;
            }
        } else if (n / C == 9) {
            str[i] = 'C'; i++;
            str[i] = 'M'; i++;
            n %= C;
        } else if (n / C >= 5) {
            str[i] = 'D'; i++;
            n -= 5*C;
        } else if (n / C == 4) {
            str[i] = 'C'; i++;
            str[i] = 'D'; i++;
            n %= C;
        } else if (n >= C) {
            t = n/C;
            for (int c = 0; c < t; c++) {
                str[i] = 'C'; i++; n-=C;
            }
        } else if (n / X == 9) {
            str[i] = 'X'; i++;
            str[i] = 'C'; i++;
            n %= X;
        } else if (n / X >= 5) {
            str[i] = 'L'; i++;
            n -= 5*X;
        } else if (n / X == 4) {
            str[i] = 'X'; i++;
            str[i] = 'L'; i++;
            n %= X;
        } else if (n >= X) {
            t = n/X;
            for (int c = 0; c < t; c++) {
                str[i] = 'X'; i++; n-=X;
            }
        } else if (n == 9) {
            str[i] = 'I'; i++;
            str[i] = 'X'; i++;
            n = 0;
        } else if (n >= 5) {
            str[i] = 'V'; i++;
            n -= 5*I;
        } else if (n == 4) {
            str[i] = 'I'; i++;
            str[i] = 'V'; i++;
            n = 0;
        } else {
            t = n/I;
            for (int c = 0; c < t; c++) {
                str[i] = 'I'; i++; n-=I;
            }
        }

    }

    return str;
}

int main() {
    FILE *f = fopen("roman.txt", "r");
    char buffer[1024], *new;
    int n=0;
    while (fgets(buffer, 1024, f)) {
        buffer[strcspn(buffer, "\n")] = 0;
        new = itor(rtoi(buffer));
        n += strlen(buffer) - strlen(new); free(new);
    }
    fclose(f);
    printf("%d", n);
    return 0;
}