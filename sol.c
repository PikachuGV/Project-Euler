/*
A common security method used for online banking is to ask the user for three random characters from a passcode. For example, if the passcode was 531278, they may ask for the 2nd, 3rd, and 5th characters; the expected reply would be: 317.
The text file, keylog.txt, contains fifty successful login attempts.
Given that the three characters are always asked for in order, analyse the file so as to determine the shortest possible secret passcode of unknown length.
*/

/*
This question can be solved by brute force.
First, get the list of digits that do appear. From simply checking we can see that only 4 and 5 are missing.
Next, we find the digit that only appears at the front. Also by checking we can see 7 is the only digit. That means 7 must be the first digit.
Converse logic shows that 0 is the last digit.
Now we just do brute force. For every remaining digit:
    1. Slot it as the next digit from the front.
    2. Check all keylogs that include this digit.
    3. If the digit is found at the second place, check that front digit is one of the previous digit.
    4. If the digit is found at the last place, check that first 2 digits both appear b4 previous digit in order.
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool seen[1000] = {false};

int main() {
    FILE *file = fopen("keylog.txt", "r");
    char buffer[64];
    int* keycodes[10]; int lKeycodes[10];
    for (int i = 0; i < 10; i++) {
        keycodes[i] = malloc(0); lKeycodes[i] = 0;
    }

    int d;
    while (fgets(buffer, 64, file)) {
        if (seen[atoi(buffer)]) continue;
        for (int j = 0; j < 3; j++) {
            d = buffer[j] - '0';
            lKeycodes[d]++;
            keycodes[d] = realloc(keycodes[d], lKeycodes[d] * sizeof(int));
            keycodes[d][lKeycodes[d] - 1] = atoi(buffer);
            seen[atoi(buffer)] = true; 
        }
    }

    
    int digitcount = 0; for (int i = 0; i < 10; i++) if (lKeycodes[i] != 0) digitcount++;


    int firstDigit;
    for (int D = 0; D < 10; D++) {
        if (lKeycodes[D] == 0) continue;
        bool out = true;
        for (int i = 0; i < lKeycodes[D]; i++) {
            if (keycodes[D][i] / 100 != D) {
                out = false; break;
            }
        }
        if (out) {
            firstDigit = D; break;
        }
    }

    bool used[10] = {false};
    int digits[digitcount]; digits[0] = firstDigit;
    used[firstDigit] = true;

    int f, s, t; bool out;
    for (int i = 1; i < digitcount; i++) {
        for (int j = 0; j < 10; j++) {
            if (used[j]) continue;
            out = true;
            for (int k = 0; k < lKeycodes[j]; k++) {
                out = false;
                f = keycodes[j][k] / 100;
                s = (keycodes[j][k] / 10) % 10;
                t = keycodes[j][k] % 10;

                if (f == j) continue;
                if (!used[f] || ((t == j) && !used[s])) {
                    out = true; break;
                }
            }

            if (!out) {
                digits[i] = j; used[j] = true; break;
            }
        }
    }


    for (int i = 0; i < digitcount; i++) printf("%d", digits[i]);
    return 0;
}