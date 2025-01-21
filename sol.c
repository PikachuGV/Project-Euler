/*
Q22: Using Q22.txt, a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.
For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 * 53 = 49714.
What is the total of all the name scores in the file?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define min(a, b) ((a < b) ? a : b)

void swap(char** a, char** b) {
    char* t = *a;
    *a = *b;
    *b = t;
}

int partition(char** names, int low, int high) {
    char* pivot = names[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {
        for (int k = 0; k < min(strlen(pivot), strlen(names[j])); k++) {
            if (names[j][k] < pivot[k]) {
                i++; swap(&names[i], &names[j]); break;
            } else if (names[j][k] > pivot[k]) {
                break;
            } else if (k == min(strlen(pivot), strlen(names[j])) - 1) {
                if (strlen(names[j]) < strlen(pivot)) {
                    i++; swap(&names[i], &names[j]); break;
                }
            }

        }

    }
    swap(&names[i + 1], &names[high]);
    return i + 1;
}

void sort(char** names, int low, int high) {
    if (low < high) {
        int pi = partition(names, low, high);

        sort(names, low, pi - 1);
        sort(names, pi + 1, high);
    } 
     
}

int main() {
    FILE* f = fopen("Q22.txt", "r");
    char buffer[100000];
    fscanf(f, "%s", &buffer);
    fclose(f);

    char name[20] = {'\0'};
    char** names = (char**)malloc(0 * sizeof(char*));
    int len = 0, c = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == ',' || i == strlen(buffer) - 1) {
            len++;
            names = (char**)realloc(names, len * sizeof(char*));
            names[len - 1] = malloc((c + 1) * sizeof(char));
            strncpy(names[len - 1], name, c + 1);
            c = 0; memset(name, '\0', sizeof(name));
        } else if (buffer[i] != '\"') {
            name[c] = buffer[i]; c++;
        }
    }

    sort(names, 0, len - 1);

    long long score, total = 0;
    for (int i = 0; i < len; i++) {
        score = 0;
        for (int j = 0; j < strlen(names[i]); j++) {
            score += names[i][j] - 'A' + 1;
        }
        total += score * (i + 1);
    }

    printf("%lld\n", total);
    return 0;
}