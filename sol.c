/*
In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way:
High Card: Highest value card.
One Pair: Two cards of the same value.
Two Pairs: Two different pairs.
Three of a Kind: Three cards of the same value.
Straight: All cards are consecutive values.
Flush: All cards of the same suit.
Full House: Three of a kind and a pair.
Four of a Kind: Four cards of the same value.
Straight Flush: All cards are consecutive values of same suit.
Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
The cards are valued in the order:2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.
If two players have the same ranked hands then the rank made up of the highest value wins; for example, a pair of eights beats a pair of fives (see example 1 below). But if two ranks tie, for example, both players have a pair of queens, then highest cards in each hand are compared (see example 4 below); if the highest cards tie then the next highest cards are compared, and so on.
Consider the following five hands dealt to two players:

Hand    Player 1                                            Player 2                                            Winner
1       5H 5C 6S 7S KD (Pair of Fives)                      2C 3S 8S 8D TD (Pair of Eights)                     Player 2
2       5D 8C 9S JS AC (Highest card Ace)                   2C 5C 7D 8S QH (Highest card Queen)                 Player 1
3       2D 9C AS AH AC (Three Aces)                         3D 6D 7D TD QD (Flush with Diamonds)                Player 2
4       4D 6S 9H QH QC (Pair of Queens Highest card Nine)   3D 6D 7H QD QS (Pair of Queens Highest card Seven)  Player 1
5       2H 2D 4C 4D 4S (Full House With Three Fours)        3C 3D 3S 9S 9D (Full House with Three Threes)       Player 1

The file, poker.txt, contains one-thousand random hands dealt to two players. Each line of the file contains ten cards (separated by a single space): the first five are Player 1's cards and the last five are Player 2's cards. You can assume that all hands are valid (no invalid characters or repeated cards), each player's hand is in no specific order, and in each hand there is a clear winner.
How many hands does Player 1 win?
*/

/*
Have two arrays when analysing the hands, one for the values and one for the suit.
Check the number of distinct values:
-5 distinct values means no repeat occur.
-4 distinct values means there is only 1 pair
-3 distinct values means there is either 2 pairs or a triplet.
-2 distinct values means there is either a 4 of a kind or a full house

We do this first to eliminate many options. If we do not get 5 distinct values, we know that we will never have a straight or a flush. 2 distinct values requires only a check of either full house or four of a kind since there is no possible higher hand (the 2 hands higher than 4 of a kind are both types of straights.) No further checks are required for 4 distinct values, because no hand higher than a pair can have only 4 distinct values. Same goes for 3 distinct values, the only check being to determine whether it is a 2 pair or a triplet.

So we only reach the next few steps if there are 5 distinct values.
We now check for a flush i.e if all suits are the same.
A simple sort (since theres only 5 cards) can help us check whether we have a straight.
There are now 4 possibilites:
1. No flush nor straight: we are left with high card. Since we already sorted the values, get the last value
2. Straight but no flush: our hand is a straight
3. Flush but no straight: hand is a flush
4. Straight flush: we now check for the presence of A. If A is present we automatically win.



Now the hard part is tiebreakers. We need to determine who has the higher pair, higher triplet or higher card.


*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void swap(int* xp, int* yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}

enum RANK {
    NONE,
    HIGH,
    PAIR,
    TWOPAIR,
    THREE,
    STRAIGHT,
    FLUSH,
    FULLHOUSE,
    FOUR,
    STRAIGHTFLUSH,
    ROYALFLUSH
};

int val(char c) {
    if (c == 'A') return 14;
    if (c == 'K') return 13;
    if (c == 'Q') return 12;
    if (c == 'J') return 11;
    if (c == 'T') return 10;
    return (int)(c - '0');
}

int nDup(int *values) {
    int hash[13] = {0}, n = 0;
    for (int i = 0; i < 5; i++) {
        if (hash[values[i] - 2] == 0) {
            n++; hash[values[i] - 2] = 1;
        }
    }
    return n;
}

struct player {
    enum RANK rank;
    char suits[6];
    int values[5];
    void(*getrank) (struct player*);
};

void getrank(struct player* p) {
    char suits[6]; for (int i = 0; i < 6; i++) suits[i] = p->suits[i];
    int values[5]; for (int i = 0; i < 5; i++) values[i] = p->values[i];
    bubbleSort(values, 5);
    int dist = nDup(values);
    if (dist == 4) p->rank = PAIR;
    else if (dist == 3) {
        if ((values)[0] != (values)[1]) {
            //The remaining 4 cards must only have 2 distinct values.
            //If the values are A and B, the only possibilities are
            //AABB,ABBB,AAAB.
            if ((values)[2] == (values)[3]) p->rank = THREE;
            else p->rank = TWOPAIR;
        } else {
            //If the first two cards have the same value, then our possibilites for the remaining 3 are
            //ABC, BBC, BCC. We only get a triplet if the third card is A.
            if ((values)[2] == (values)[0]) p->rank = THREE;
            else p->rank = TWOPAIR;
        }
    }
    else if (dist == 2) {
        //Either 4 of a kind or full house.
        //Possibilities are:
        //AAABB,AAAAB,AABBB,ABBBB
        if ((values)[1] == (values)[3]) p->rank = FOUR;
        else p->rank = FULLHOUSE;
    } else {
        //We are now left with distinct values only.
        bool hasFlush = true, hasStraight = true;
        
        for (int i = 1; i < 5; i++) {
            if (suits[i] != suits[i-1]) hasFlush = false;
            if ((values)[i] != (values)[i-1] + 1) hasStraight = false;
            if (!hasFlush && !hasStraight) p->rank = HIGH;
        }
    
        if (hasStraight && hasFlush) {
            if ((values)[4] == 14) p->rank = ROYALFLUSH;
            else p->rank = STRAIGHTFLUSH;
        }
    
        else if (hasStraight) p->rank = STRAIGHT;
    
        else if (hasFlush) p->rank = FLUSH;
    }
}

bool isWin(struct player p1, struct player p2) {
    p1.getrank(&p1); p2.getrank(&p2);

    if (p1.rank > p2.rank) return true;
    if (p1.rank < p2.rank) return false;

    int hash1[13] = {0}, hash2[13] = {0};
    for (int i = 0; i < 5; i++) {
        hash1[p1.values[i] - 2]++; hash2[p2.values[i]-2]++;
    }

    int max;
    if (p1.rank == FOUR) max = 4;
    else if ((p1.rank == THREE) || (p1.rank == FULLHOUSE)) max = 3;
    else if ((p1.rank == PAIR) || (p1.rank == TWOPAIR)) max = 2;
    else max = 1;

    for (max; max > 0; max--) {
        if (p1.rank == FOUR && ((max == 2) || (max == 3))) continue;
        if (p1.rank == THREE && max == 2) continue;
        for (int i = 12; i >= 0; i--) {
            if ((hash1[i] == max) && (hash2[i] < max)) return true;
            if ((hash2[i] == max) && (hash1[i] < max)) return false;
        }
    }
    exit(12141);
}

int main() {
    clock_t start = clock();
    char buffer[10000], *token;
    char suits[6]; suits[5] = '\0';
    int values[5], index = 0, win = 0, i = 0;
    struct player p1 = {NONE, {'\0'}, {0}, getrank}, p2 = {NONE, {'\0'}, {0}, getrank}, *players[] = {&p1, &p2}, *currplayer;
    FILE *f;

    f = fopen("poker.txt", "r");
    while (fgets(buffer, sizeof(buffer), f)) {
        i++;
        if (i == 516) {
            i = 516;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        token = strtok(buffer, " ");
        while (token != NULL ) {
            currplayer = players[index/5];
            currplayer->values[index%5] = val(token[0]);
            currplayer->suits[index%5] = token[1];
            token = strtok(NULL, " ");
            index++;
        }
        if (isWin(p1, p2)) win++;
        index = 0;
    }

    printf("%d\n",win);

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken in seconds: %lfs\n", time);
    return 0;
}