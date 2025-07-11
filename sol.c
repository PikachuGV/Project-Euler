/*
In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by only moving to the right and down, is indicated in bold red and is equal to 2427.


131 673 234 103 18
201 96  342 965 150
630 803 746 422 111
537 699 497 121 956
805 732 524 37  331


Find the minimal path sum from the top left to the bottom right by only moving right and down in matrix.txt, a 31K text file containing an 80 by 80 matrix.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define min(a,b) ((a < b) ? a : b)

int matrix[80][80]; int minsum[80][80] = {0};

int search(int i, int j) {
    if (i == 79 && j == 79) return matrix[i][j];
    if (minsum[i][j] != 0) return minsum[i][j];

    int eval = INT_MAX;
    if (i < 79) eval = min(eval,search(i+1, j));
    if (j < 79) eval = min(eval,search(i, j+1));

    minsum[i][j] = eval + matrix[i][j];

    return minsum[i][j];
}


int main() {
    FILE *f = fopen("matrix.txt", "r");
    char buffer[1023], *token;
    for (int i = 0; i < 80; i++) {
        fgets(buffer, 1023, f);
        token = strtok(buffer, ",");
        for (int j = 0; j < 80; j++) {
            matrix[i][j] = atoi(token);
            token = strtok(NULL, ",");
        }
    }

    printf("%d\n", search(0,0));
    return 0;
}