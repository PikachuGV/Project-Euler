/*
By replacing each of the letters in the word CARE with 1, 2, 9, and 6 respectively, we form a square number: 1296 = 36^2. What is remarkable is that, by using the same digital substitutions, the anagram, RACE, also forms a square number: 9216 = 96^2. We shaULL caULL CARE (and RACE) a square anagram word pair and specify further that leading zeroes are not permitted, neither may a different letter have the same digital value as another letter.
Using words.txt, a 16K text file containing nearly two-thousand common English words, find all the square anagram word pairs (a palindromic word is NOT considered to be an anagram of itself).
What is the largest square number formed by any member of such a pair?
NOTE: All anagrams formed must be contained in the given text file.
*/

/*
Not even gna try explaining what this does cos its too much of a headacher
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define max(a,b) ((a>b) ? a :b)
typedef unsigned long long ULL;

const ULL PRIMES[] = {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL, 41ULL, 43ULL, 47ULL, 53ULL, 59ULL, 61ULL, 67ULL, 71ULL, 73ULL, 79ULL, 83ULL, 89ULL, 97ULL, 101ULL};

const int TENS[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};


ULL scorestr(char *str) {
    ULL prod = 1ULL;
    for (int i = 0; i < strlen(str); i++) {
        prod *= PRIMES[str[i] - 'A'];
    }

    return prod;
}

ULL scoreint(int n) {
    ULL prod = 1ULL;
    while (n != 0) {
        prod *= PRIMES[n%10];
        n/=10;
    }
    return prod;
}

int cmpint(const void *a, const void *b) {
    int ia = *(int *)a, ib = *(int *)b;
    ULL proda = scoreint(ia), prodb = scoreint(ib);
    if (proda < prodb) return -1;
    if (proda > prodb) return 1;
    if (proda == prodb) return 0; 
}

int cmpstr(const void *a, const void *b) {
    char *stra = *(char **)a, *strb = *(char **)b;
    ULL proda = scorestr(stra), prodb = scorestr(strb);
    if (proda < prodb) return -1;
    if (proda > prodb) return 1;
    if (proda == prodb) return 0; 
}

int *squares(int n, int *l) {
    *l = 0;
    int *arr = malloc(0);
    for (int i = 1; i * i <= n; i++) {
        (*l)++;
        arr = realloc(arr, (*l)*sizeof(int));
        arr[*l - 1] = i*i;
    }

    return arr;
}

int ndigits(int n) {
    if (n < 0) n *= -1;
    if (n == 0) return 1;
    for (int i = 1; i < 10; i++) {
        if (n < TENS[i]) return i;
    }

    exit(1000);
}

bool hasWord(char **words, int len, char *word) {
    for (int i = 0; i < len; i++) {
        if (strcmp(words[i], word) == 0) return true;
    }
    return false;
}

int search(char **words, int l, int *sq, int idx, ULL s) {
    int d = ndigits(sq[idx]), n1, n2, keyviachar[26] = {0};
    char *word, *newword = calloc(d+1, sizeof(char)), keyviaint[10] = {0};
    bool out = false;
    
    while (s == scoreint(sq[idx-1]) && idx != 0) {
        n1=sq[idx]; n2=sq[idx-1];
        for (int i = l-1; i >= 0; i--) {
            memset(keyviaint, 0, sizeof(keyviaint));
            memset(keyviachar, 0, sizeof(keyviachar));
            out = false;
            word = words[i];
            if (strlen(word) != d) continue;
    
            for (int k = d-1; k >= 0; k--) {
                if ((keyviachar[word[k]-'A'] != 0) && (keyviachar[word[k]-'A'] != (n1%10))) {out = true;break;}
                if (keyviachar[word[k]-'A'] == 0) {
                    keyviaint[n1%10] = word[k];
                    keyviachar[word[k]-'A'] = n1%10;
                }
                n1 /= 10;
            }
    
            n1 = sq[idx];
            if (out) continue;
    
            for (int k = d-1; k>=0; k--) {
                newword[k] = keyviaint[n2%10];
                n2/=10;
            }
    
            n2 = sq[idx-1];
            if (hasWord(words, l, newword) == true) {
                printf("%s, %d, %s, %d\n",word,n1,newword,n2);
                return max(n1, n2);
            };
        }
        idx--;
    }

    return 0;
}



int main() {
    FILE *f = fopen("words.txt","r");
    char buffer[100000], word[32];
    char **words = malloc(0); 
    int c = 0, a = 0;
    fscanf(f, "%s", &buffer); fclose(f);

    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == ',' || i == strlen(buffer) - 1) {
            a++;
            words = realloc(words, a * sizeof(char *)); 
            words[a-1] = malloc((strlen(word)+1)*sizeof(char));
            strcpy(words[a-1], word);
            memset(word, '\0', sizeof(word)); c=0;
        } else if (buffer[i] != '\"') {
            word[c] = buffer[i]; c++;
        }
    }

    qsort(words, a, sizeof(char*), cmpstr);

    int s, C=0;
    char **temp = malloc(a*sizeof(char*));
    for (int i = a-1; i >= 1; i--) {
        s = scorestr(words[i]);
        if (s == scorestr(words[i-1])) {
            temp[C] = malloc((strlen(words[i])+1)*sizeof(char));
            strcpy(temp[C], words[i]); C++;
            while (s == scorestr(words[i-1]) && i != 0) {
                i--;
                temp[C] = malloc((strlen(words[i])+1)*sizeof(char));
                strcpy(temp[C], words[i]); C++;
            }
        }
    }

    free(words); words = realloc(temp, C*sizeof(char*)); a=C;

    int l = 0, *sq = squares(999999, &l);
    int ans = 0;
    qsort(sq, l, sizeof(int), cmpint);
    
    for (int i = l-1; i > 0; i--) {
        s = scoreint(sq[i]);
        if (s == scoreint(sq[i-1])) {
            ans = max(search(words, a, sq, i, s), ans);
        }
    }

    printf("%d ", ans);


    return 0;
}