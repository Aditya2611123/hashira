#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long base_to_decimal(const char *s, int base) {
    long long number = 0;
    while (*s) {
        char c = *s;
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            digit = 0; // Invalid, but assume 0
        }
        number = number * base + digit;
        s++;
    }
    return number;
}

int main() {
    int n = 10;
    int k = 7;
    char* roots_value[10] = {
        "13444211440455345511",
        "aed7015a346d635",
        "6aeeb69631c227c",
        "e1b5e05623d881f",
        "316034514573652620673",
        "2122212201122002221120200210011020220200",
        "20120221122211000100210021102001201112121",
        "20220554335330240002224253",
        "45153788322a1255483",
        "1101613130313526312514143"
    };
    int bases[10] = {6, 15, 15, 16, 8, 3, 3, 6, 12, 7};
    
    long long *decimal_roots = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        decimal_roots[i] = base_to_decimal(roots_value[i], bases[i]);
    }
    
    // We need k roots, so take the first k
    long long *selected_roots = (long long*)malloc(k * sizeof(long long));
    for (int i = 0; i < k; i++) {
        selected_roots[i] = decimal_roots[i];
    }
    
    // Initialize dp for dynamic programming: dp[i] = sum of products of i roots
    long long *dp = (long long*)calloc(k+1, sizeof(long long));
    dp[0] = 1;
    for (int i = 0; i < k; i++) {
        long long r = selected_roots[i];
        for (int j = k; j >= 1; j--) {
            dp[j] += dp[j-1] * r;
        }
    }
    
    // The polynomial is x^k + a_{k-1} x^{k-1} + ... + a0
    // The coefficient for x^{k-i} is (-1)^i * dp[i]
    printf("The coefficients of the polynomial are:\n");
    for (int i = 0; i <= k; i++) {
        long long coeff = dp[i];
        if (i % 2 == 1) {
            coeff = -coeff;
        }
        printf("x^%d: %lld\n", k - i, coeff);
    }
    
    free(decimal_roots);
    free(selected_roots);
    free(dp);
    return 0;
}