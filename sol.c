/*
Comparing two numbers written in index form like 2^11 and 3^7 is not difficult, as any calculator would confirm that 2^11 = 2048 < 3^7 = 2187.
However, confirming that 632382^518061 > 519432^525806 would be much more difficult, as both numbers contain over three million digits.
Using base_exp.txt, a 22K text file containing one thousand lines with a base/exponent pair on each line, determine which line number has the greatest numerical value.
NOTE: The first two lines in the file represent the numbers in the example given above.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
        printf(" ");
    }
    puts("");
}

double log2_fast(double x) {
    //double x = (1 + M/(2^52)) * 2^(E-1023)
    //log2 x = E - 1023 + log2 (1 + M/(2^52))
    //       ~ E - 1023 + M/(2^52)
    // bit representation of x when read as integer converts to E * 2^52 + M
    //since M is 52 bits we thus know that log2 x ~ (E-1023) + 0.M
    //

    const double error = 0.03125;


    long long bit_rep = * (long long *) &x;
    long long E = ((bit_rep >> 52) & 0x7FF)-1023;
    long long tempM = ((bit_rep & 0xFFFFFFFFFFFFF) | ((long long)0x3FF << 52));
    double M = (* (double *) &tempM) - 1;
    double ans = E + M + 0.0450466;


    return ans;
}


int main() {
    FILE *f = fopen("base_exp.txt", "r");
    char buffer[256], *ptr;
    double base, exp, result, maxresult = 0; //a^b = bloga
    int line = 1, maxline;
    while (fgets(buffer, 256, f)) {
        ptr = strtok(buffer, "," );
        base = atof(ptr);
        ptr = strtok(NULL, ",");
        exp = atof(ptr);
        result = exp * log2(base);
        if (result > maxresult) {
            maxresult = result;
            maxline = line;
        }
        line++;
    }

    printf("%d\n", maxline);

    printf("%lf, %lf",log2(895447),log2_fast(895447));
    return 0;

//1047, 
}