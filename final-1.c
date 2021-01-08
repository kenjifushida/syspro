#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int multiply(int x, int res[], int digits) {
    int carry = 0;
    for(int i = 0; i < digits; i++) {
        int prod = res[i]*x + carry;
        res[i] = prod % 10;
        
        // put rest in carry
        carry = prod/10;
    }

    while(carry) {
        res[digits] = carry % 10;
        carry = carry/10;
        digits++;
    }
    return digits;
}


int *power(int x, int n, int res[]) {
    if(n == 0){
        printf("1\n");
        return 0;
    }

    int digits = 0;
    int temp = x;

    while(temp!= 0) {
        res[digits++] = temp % 10;
        temp = temp / 10;
    }

    for (int i = 2; i <= n;i++) {
        digits = multiply(x, res, digits);
    }

    return res;
}

void printresult(int res[], unsigned long size) {
    for (int i = size; i >= 0; i--) {
        printf("%d",res[i]);
    }
    return;
}

void printcomma(int res[], unsigned long size) {
    for (int i = size; i >= 0; i--) {
        printf("%d",res[i]);
        if (i % 3 == 0 && i != 0) {
            printf(",");
        }
    }
    return;
}

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        int n = atoi(argv[1]);
        unsigned long size = floor(n*log10(2));
        int base = 2;
        int res[size];
        int *result;
        result = power(base, n, res);
        if (argc > 2)
        {
            if (strcmp(argv[2], "+") == 0)
            {
                printcomma(result, size);
            }
            return 0;
        }
        printresult(result, size);
    }
    return 0;
}