/*
Paste question here.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}


#define max(a,b) ((a > b) ? a : b)

int cmp(char *a, char *b) {
    char *dpa = strchr(a, '.'), *dpb =strchr(b, '.'); 
    int ordera = (dpa == NULL) ? strlen(a) : dpa - a;
    int orderb = (dpb == NULL) ? strlen(b) : dpb - b;

    if (ordera != orderb) return ordera-orderb;


    if (strncmp(a, b, ordera) != 0) return strncmp(a, b, ordera);
    if (dpa == NULL && dpb != NULL) return -1;
    if (dpb == NULL && dpa != NULL) return 1;
    if (dpa == NULL && dpb == NULL) return 0;
    return strcmp(dpa+1, dpb+1);
}

void dtoi(char *a, char **ba, int *offset) {
    //ia, da are integer and decimal parts of a. ib, db are integer and decimal parts of b
    char *i, *d;
    //ordera and orderb are the orders of magnitude of the integer parts of a and b.
    int order;

    //Find whether arguments have decimals
    char *decimalpt = strchr(a, '.');

    if (decimalpt == NULL) {
        *ba = calloc(strlen(a)+1, sizeof(char));
        strcpy(*ba, a);
        *offset = 0; return;
    }

    //Get order of magnitudes
    order = decimalpt - a;

    //Initialise i and d for both a and b
    i = calloc(order + 1, sizeof(char));
    d = calloc(strlen(a) - order, sizeof(char));
    
    //Store i and d for both a and b
    strncpy(i, a, order);
    if (decimalpt != NULL) strncpy(d, decimalpt+1, strlen(a)-order-1);

    //Get offset amount
    *offset = strlen(d);

    if (decimalpt == a+1 && a[0] == '0') {
        free(i);
        *ba = d;
        return;
    }

    //Concat the integer and decimals to form a big integer.
    *ba = calloc(strlen(i) + strlen(d) + 1, sizeof(char));
    strcat(*ba, i); strcat(*ba, d);

    //Free memory
    free(i); free(d);
    return;
}

void *baloff(char **a, char **b, int offseta, int offsetb) {
    if (offseta > offsetb) {
        *b = realloc(*b, (strlen(*b)+offseta-offsetb+1) * sizeof(char)); 
        (*b)[strlen(*b)+offseta-offsetb] = '\0';
        memset(*b+strlen(*b), '0', (offseta-offsetb)*sizeof(char));
    } else if (offseta < offsetb) {
        *a = realloc(*a, (strlen(*a)+offsetb-offseta+1) * sizeof(char)); 
        (*a)[strlen(*a)+offsetb-offseta] = '\0';
        memset(*a+strlen(*a), '0', (offsetb-offseta)*sizeof(char));
    }
}

char *udos(char *a, int offset) {
    char *offsetted;
    if (offset >= strlen(a)) {
        offsetted = calloc(offset + 3, sizeof(char));
        memset(offsetted, '0', (offset-strlen(a)+2)*sizeof(char));
        offsetted[1] = '.';
        strcat(offsetted, a);
    } else {
        offsetted = calloc(strlen(a) + 2, sizeof(char));
        strncat(offsetted, a, strlen(a)-offset);
        strcat(offsetted, ".");
        strcat(offsetted, a+strlen(a)-offset);
    }
    return offsetted;
}

char *iadd(char *a, char *b) {
    //Set A and B depending on which argument has the greater length.
    char *A, *B, *c;
    if (strlen(a) > strlen(b)) {
        A = calloc(strlen(a) + 1, sizeof(char)); B = calloc(strlen(a) + 1, sizeof(char));
        strcpy(A, a); strcpy(B + (strlen(a) - strlen(b)), b);
        memset(B, '0', (strlen(a) - strlen(b)) * sizeof(char));
    } else {
        A = calloc(strlen(b) + 1, sizeof(char)); B = calloc(strlen(b) + 1, sizeof(char));
        strcpy(A, b); strcpy(B + (strlen(b) - strlen(a)), a);
        memset(B, '0', (strlen(b) - strlen(a)) * sizeof(char));
    }

    c = calloc(strlen(A) + 1, sizeof(char));
    int digit, carry = 0;

    for (int i = strlen(A) - 1; i >= 0; i--) {
        digit = (A[i] - '0') + (B[i] - '0') + carry;
        carry = digit / 10;
        c[i] = (digit % 10) + '0';
    }

    free(A); free(B);

    if (carry != 0) {
        char *C = calloc(strlen(c) + 2, sizeof(char));
        strcpy(C+1, c); C[0] = carry + '0';
        free(c);
        return C;
    }
    return c;
}

char *add(char *a, char *b) {
    //For consistency, we will use the offset method similiar to subtraction.

    char *ba, *bb; int offseta, offsetb, offsetMag; 
    dtoi(a, &ba, &offseta);
    dtoi(b, &bb, &offsetb);
    
    if (atoi(bb) == 0) {
        char *c = calloc(strlen(a) + 1, sizeof(char)); strcpy(c, a);
        return c;
    }
    if (atoi(ba) == 0) {
        char *c = calloc(strlen(b) + 1, sizeof(char)); strcpy(c, b);
        return c;
    }

    //Add trailing zeros if needed
    offsetMag = max(offseta, offsetb);
    baloff(&ba, &bb, offseta, offsetb);

    char *sum = iadd(ba,bb);
    free(ba); free(bb);

    //Undo offset and add leading zeros for bigger offsets
    if (offsetMag == 0) return sum;

    char *sumOffsetted = udos(sum, offsetMag);

    free(sum);

    return sumOffsetted;
}

char *isub(char *a, char *b) {
    char *c = calloc(strlen(a) + 1, sizeof(char)); c[0] = '0';
    if (cmp(a,b) == 0) return c;
    if (cmp(a,b) < 0) return c;
    char *tempa = calloc(strlen(a) + 1, sizeof(char)); strcpy(tempa, a);
    char *newb = calloc(strlen(a) + 1, sizeof(char));
    strcpy(newb + (strlen(a) - strlen(b)), b);
    memset(newb, '0', (strlen(a) - strlen(b)) * sizeof(char));
    
    char A, B;
    int start = 0;
    for (int i = strlen(newb) - 1; i >= 0; i--) {
        B = newb[i];
        A = tempa[i];
        if (A == B) {
            c[i] = '0';
        } else if (A > B) {
            c[i] = A - B + '0';
            start = i;
        } else {
            c[i] = A - B + 10 + '0';
            for (int j = i - 1; j >= 0; j--) {
                if (tempa[j] > '0') {
                    tempa[j]--;
                    break;
                } else {
                    tempa[j] = '9';
                }
            }
            start = i;
        }
    }
    free(tempa); free(newb);
    char *C = calloc(strlen(c)+1, sizeof(char));
    strcpy(C, c+start); free(c); return C;
}

char *sub(char *a, char *b) {
    //Since we do not want to deal with negative numbers, we will convert the decimal numbers into integers to do the subtraction. Assume here that a >= b

    
    char *ba, *bb; int offseta, offsetb, offsetMag; 
    dtoi(a, &ba, &offseta);
    dtoi(b, &bb, &offsetb);
    
    if (atoi(bb) == 0) {
        char *c = calloc(strlen(a) + 1, sizeof(char)); strcpy(c, a);
        return c;
    }

    //Add trailing zeros if needed
    offsetMag = max(offseta, offsetb);
    baloff(&ba, &bb, offseta, offsetb);

    char *diff = isub(ba,bb);
    free(ba); free(bb);

    //Undo offset and add leading zeros for bigger offsets
    if (offsetMag == 0) return diff;

    char *diffOffsetted = udos(diff, offsetMag);

    free(diff);

    return diffOffsetted;
}

char *imul(char *a, char *b) {
    char *prod = calloc(2, sizeof(char)); prod[0] = '0';
    if (atoi(a) == 0 || atoi(b) == 0) return prod;
    char *A, *B;
    if (strlen(a) > strlen(b)) {
        A = calloc(strlen(a)+1, sizeof(char)); strcpy(A, a);
        B = calloc(strlen(b)+1, sizeof(char)); strcpy(B, b);
    } else {
        A = calloc(strlen(b)+1, sizeof(char)); strcpy(A, b);
        B = calloc(strlen(a)+1, sizeof(char)); strcpy(B, a);
    }

    char *temp = calloc(strlen(A) + 1, sizeof(char));
    char *temp2, *sum;
    int dA, dB, carry, digit;
    for (int i = 0; i < strlen(B) ; i++) {
        temp = realloc(temp, (strlen(A) + i + 1) * sizeof(char));
        memset(temp, '\0', strlen(A) * sizeof(char));
        memset(temp + strlen(A), '0', i * sizeof(char));
        temp[strlen(A)+i] = '\0';
        dB = B[strlen(B)-i-1] - '0'; carry = 0;
        for (int j = strlen(A) - 1; j >= 0; j--) {
            dA = A[j] - '0';
            digit = dB * dA + carry;
            carry = digit / 10;
            temp[j] = (digit % 10) + '0';
        }
        if (carry != 0) {
            temp2 = calloc(strlen(A) + i + 2, sizeof(char)); temp2[0] = carry + '0';
            strcat(temp2, temp); free(temp); temp = temp2;            
        }
        sum = iadd(prod, temp);
        prod = realloc(prod, (strlen(sum)+1)*sizeof(char));
        strcpy(prod, sum); free(sum);
    }
    return prod;
}

char *mul(char *a, char *b) {
    //Similiar to subtraction, we convert the decimal arguments into integers via an offset.
    //The final answer offset will be the sum of offsets of both arguments.
    
    char *ba, *bb; int offseta, offsetb;
    dtoi(a, &ba, &offseta);
    dtoi(b, &bb, &offsetb);

    int offsetMag = offseta + offsetb;
    char *prod = imul(ba, bb);
    free(ba); free(bb);

    //Undo offset and add leading zeros for bigger offsets
    if (offsetMag == 0) return prod;
    
    char *prodOffset = udos(prod, offsetMag);
    free(prod);
    return prodOffset;
}

char *divide(char *a, char *b, int nDecimals) {
    /*
    It is easier to do long division when the divisor is an integer.
    Thus we will offset b into an integer first, after which we offset a by the same amount.

    Now we do long division. When we pass the decimal point, the quotient will have a decimal.

    nDecimals will set the number of decimal places returned. If the most significant digit of the quotient appears after the number of decimal places given, then the function will return up till the most significant digit
    */
    if (atoi(a) == 0) {
        char *c = calloc(2, sizeof(char)); c[0] = '0';
        return c;
    }
   
    char *ba, *bb, *tempba; int offseta, offsetb;
    dtoi(b, &bb, &offsetb);
   
    //Offset a by offsetb. If offseta > offsetb, then we can just offset a normally and then undo the offset by (offseta - offsetb). If offsetb > offseta, then we add (offsetb - offseta) zeros after ba.
    dtoi(a, &ba, &offseta);
    if (offseta > offsetb) {
       tempba = udos(ba, offseta-offsetb);
       free(ba); ba = tempba;
    } else {
        ba = realloc(ba, (strlen(ba)+offsetb-offseta+1)*sizeof(char));
        ba[strlen(ba)+offsetb-offseta] = '\0';
        memset(ba+strlen(ba), '0', (offsetb-offseta)*sizeof(char));
    }
    
    char *digits[] = {"0","1","2","3","4","5","6","7","8","9","10"};
    char *table[11];
    for (int i = 0; i < 11; i++) table[i] = mul(bb, digits[i]);

    char *decimal = strchr(ba, '.');
    int decimalidx = decimal ? decimal - ba : -1;

    char *quotient = calloc(strlen(ba) + max(decimalidx,0) + nDecimals + 2, sizeof(char)); int qidx = 0;
    char *dividend = calloc(max(strlen(ba),strlen(bb))+2, sizeof(char)); int didx = 0;
    char *remainder;
    int start = -1, nd = 0;

    for (int i = 0; i < strlen(ba); i++) {
        if (dividend[0] == '0') didx = 0;
        if (i == decimalidx) {
            quotient[qidx] = '.'; qidx++; continue;
        }

        dividend[didx] = ba[i]; didx++;
        remainder = NULL;
        for (int j = 0; j < 10; j++) {
            if (cmp(dividend, table[j+1])<0) {
                remainder = sub(dividend, table[j]); 
                quotient[qidx] = '0'+j; qidx++;
                if (j > 0 && start == -1) {
                    start = (i > decimalidx && decimalidx != -1) ? decimalidx-1 : i;
                }
                if (i > decimalidx && decimalidx != -1) nd++;
                break;
            }
        }
        memset(dividend, 0, strlen(dividend)*sizeof(char));
        strcpy(dividend, remainder); didx = strlen(dividend);
        free(remainder);

        if (nd == nDecimals && start != -1) break;
    }

    if (decimalidx == -1) {quotient[qidx] = '.'; decimalidx = qidx; qidx++;}

    while (nd < nDecimals || start == -1) {
        if (dividend[0] == '0') didx = 0;
        dividend[didx] = '0'; didx++;
        remainder = NULL;
        for (int j = 0; j < 10; j++) {
            if (cmp(dividend, table[j+1])<0) {
                remainder = sub(dividend, table[j]); 
                quotient[qidx] = '0'+j; qidx++;
                if (j > 0 && start == -1) start = decimalidx-1;
                nd++;break;
            }
        }
        memset(dividend, 0, strlen(dividend)*sizeof(char));
        strcpy(dividend, remainder); didx = strlen(dividend);
        free(remainder);
    }


    char *truncate = calloc(strlen(quotient)+1-start, sizeof(char));
    strncpy(truncate, quotient+start, strlen(quotient)-start);
    free(quotient);

    return truncate;
}

bool *squares(int n) {
    bool *arr = calloc(n+1, sizeof(int));
    for (int i = 0; i * i <= n; i++) {
        arr[i * i] = true;
    }

    return arr;
}


int main() {
    double start = get_time();
    bool *sq = squares(100);
    char *a, *n, *frac, *sum, *temp;
    int dsum = 0;
    for (int N = 1; N <= 100; N++) {
        if (sq[N]) continue;
        a = calloc(3,sizeof(char)); n = calloc(3, sizeof(char));
        sprintf(a, "%d", N); sprintf(n, "%d", N);

        for (int i = 0; i < 11; i++) {
            frac = divide(n, a, 200);
            sum = add(a, frac);
            temp = divide(sum, "2", 200);

            a = realloc(a, (strlen(temp)+1)*sizeof(char));
            strcpy(a, temp); free(temp);
            free(frac); free(sum);
        }

        dsum += a[0]-'0';
        for (int i = 0; i < 99; i++) {
            dsum += *(strchr(a,'.')+1+i) - '0';
        }
        free(a); free(n);
    }
    printf("%d\nTime taken:%lf", dsum, get_time()-start);
}