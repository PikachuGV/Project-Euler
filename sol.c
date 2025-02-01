/*
The nth term of the sequence of triangle numbers is given by, tn = n(n+1)/2; so the first ten triangle numbers are:
1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.
Using words.txt, a 16K text file containing nearly two-thousand common English words, how many are triangle words?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int value(char* str) {
    int score = 0;
    for (int i = 0; i < strlen(str); i++) {
        score += (int)str[i] - 64;
    }

    return score;
}

bool isTriangular(int n) {
    int N = 8 * n + 1;
    for (int i = 0; i * i <= N; i++) {
        if (i * i == N) return true;
    }
    return false;
}

int main() {
    char buffer[100000], word[20];
    int C, c, score;
    FILE* f;

    f = fopen("0042_words.txt", "r");
    fscanf(f, "%s", &buffer); fclose(f);

    memset(word, '\0', sizeof(word));

    C = 0; c = 0;

    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == ',' || i == strlen(buffer) - 1) {
            score = value(word);
            if (isTriangular(score)) C++;
            memset(word, '\0', sizeof(word)); c=0;
        } else if (buffer[i] != '\"') {
            word[c] = buffer[i]; c++;
        }
    }

    printf("%d\n", C);
    return 0;
}