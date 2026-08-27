#include <stdio.h>
#include <string.h>

long long binaryconv(char* str) {
    long long num = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\n') continue;
        num = num * 2 + (str[i] - '0');
    }
    return num;
}

void printBinary(long long n) {
    if (n > 1) {
        printBinary(n / 2);
    }
    printf("%lld", n % 2);
}

long long karatsuba(long long num1, long long num2) {
    if (num1 < 2 || num2 < 2) {
        return num1 * num2;
    }

    long long maxVal = (num1 > num2) ? num1 : num2;
    int bits = 0;
    while (maxVal > 0) {
        bits++;
        maxVal = maxVal / 2;
    }

    int mid = (bits + 1) / 2;
    long long split = 1LL << mid; 

    long long left1 = num1 / split;
    long long right1 = num1 % split;
    
    long long left2 = num2 / split;
    long long right2 = num2 % split;
    
    long long prodLeft = karatsuba(left1, left2);
    long long prodRight = karatsuba(right1, right2);
    long long prodSum = karatsuba(left1+right1,left2+right2);
    
    long long midTerm = (prodSum - prodLeft - prodRight) * split;
    long long highTerm = prodLeft * split * split;
    
    return highTerm + midTerm + prodRight;

}

int main() {
    char binStr1[64], binStr2[64];
    
    // printf("Enter 1st binary number- ");
    scanf("%s", binStr1);
    
    // printf("Enter 2nd binary number- ");
    scanf("%s", binStr2);

    long long num1 = binaryconv(binStr1);
    long long num2 = binaryconv(binStr2);

    long long result = karatsuba(num1, num2);
    
    printBinary(result);
    printf("\n");
    
    return 0;
}
