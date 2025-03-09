/*
Each character on a computer is assigned a unique code and the preferred standard is ASCII (American Standard Code for Information Interchange). For example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.

A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each byte with a given value, taken from a secret key. The advantage with the XOR function is that using the same encryption key on the cipher text, restores the plain text; for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.

For unbreakable encryption, the key is the same length as the plain text message, and the key is made up of random bytes. The user would keep the encrypted message and the encryption key in different locations, and without both "halves", it is impossible to decrypt the message.

Unfortunately, this method is impractical for most users, so the modified method is to use a password as a key. If the password is shorter than the message, which is likely, the key is repeated cyclically throughout the message. The balance for this method is using a sufficiently long password key for security, but short enough to be memorable.

Your task has been made easy, as the encryption key consists of three lower case characters. Using 0059_cipher.txt, a file containing the encrypted ASCII codes, and the knowledge that the plain text must contain common English words, decrypt the message and find the sum of the ASCII values in the original text
*/

/*
Printable characters have ascii values between 32 and 127 inclusive.
Ascii values of lowercase letters range from 97 to 122
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int countChar(char *str, char c) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) count++;
    }
    return count;
}

int main() {
    char buffer[10000];
    FILE *f = fopen("0059_cipher.txt", "r");
    fgets(buffer, 10000, f);
    fclose(f);

    char encrypted[countChar(buffer, ',') + 2]; memset(encrypted, '\0', sizeof(encrypted));
    char *token = strtok(buffer, ",");
    for (int i = 0; i < sizeof(encrypted) / sizeof(char); i++) {
        encrypted[i] = atoi(token);
        token = strtok(NULL, ",");
    }

    

    char key[3], decrypted[sizeof(encrypted) / sizeof(char)]; memset(decrypted, '\0', sizeof(decrypted));
    char decryptedchar; bool out = false;
    for (int i = 0; i < 3; i++) {
        for (int curr = 97; curr <= 122; curr++) {
            out = false;
            for (int index = i; index < sizeof(encrypted) / sizeof(char) - 1; index += 3) {
                decryptedchar = encrypted[index] ^ curr;
                if (
                    decryptedchar > 125                             || 
                    decryptedchar < 32                              || 
                    (decryptedchar > 34 && decryptedchar < 39)      ||
                    decryptedchar == 42                             ||
                    (decryptedchar >= 60 && decryptedchar <= 62)    ||
                    decryptedchar == 64                             ||
                    (decryptedchar >= 94 && decryptedchar <= 96)
                ) {
                    out = true;
                    break;
                }
                decrypted[index] = decryptedchar;
            }
            if (!out) {
                printf("%c\n", curr);break;
            } 
        }
    }

    int sum = 0;
    for (int i = 0; i < strlen(decrypted) + 1; i++) {
        sum += decrypted[i];
    }
    printf("%d\n", sum);



    return 0;
}