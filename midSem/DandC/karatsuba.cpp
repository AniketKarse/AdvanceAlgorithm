#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int getLength(long long value) {
    int count = 0;
    while (value > 0) {
        count++;
        value /= 10;
    }
    return count;
}
long long intPow(long long base, int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10) {
        return x * y;
    }

    int n = max(getLength(x), getLength(y));
    int half = n / 2;
    long long multiplier = intPow(10, half);

    long long xl = x / multiplier;
    long long xr = x % multiplier;
    long long yl = y / multiplier;
    long long yr = y % multiplier;

    long long p1 = karatsuba(xl,yl);
    long long p2 = karatsuba(xr,yr);
    long long p3 = karatsuba(xl+xr,yl+yr);

    long long middleterm = p3 - p1 - p2;

    return p1 * intPow(10, 2 * half) + (middleterm * multiplier) + p2;
}

int main() {
    long long num1 = 1234;
    long long num2 = 5678;
    
    cout << "Karatsuba Product: " << karatsuba(num1, num2) << endl;
    cout << "Standard Product:  " << (num1 * num2) << endl;
    
    return 0;
}
