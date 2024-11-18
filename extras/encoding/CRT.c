
#include <stdio.h>

// Function to return the Greatest Common Divisor (GCD)
int gcdExtended(int a, int b, int *x, int *y) {
    // Base Case
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    // Update x and y using results of recursive call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

// Function to find modulo inverse of a under modulo m
int modInverse(int a, int m) {
    int x, y;
    int g = gcdExtended(a, m, &x, &y);
    if (g != 1) {
        printf("Inverse doesn't exist\n");
        return -1;
    } else {
        // m is added to handle negative x
        int res = (x % m + m) % m;
        return res;
    }
}

// Function to apply the Chinese Remainder Theorem
int chineseRemainderTheorem(int num[], int rem[], int k) {
    // Compute product of all numbers
    int prod = 1;
    for (int i = 0; i < k; i++)
        prod *= num[i];

    // Initialize result
    int result = 0;

    // Apply the formula:
    // result = (a1 * m1 * inv1 + a2 * m2 * inv2 + ... + ak * mk * invk) % prod
    for (int i = 0; i < k; i++) {
        int pp = prod / num[i];
        int inv = modInverse(pp, num[i]);
        if (inv == -1) {
            return -1; // Modular inverse doesn't exist
        }
        result += rem[i] * pp * inv;
    }

    return result % prod;
}

int main() {
    int k;
    
    // Take number of equations as input
    printf("Enter number of equations: ");
    scanf("%d", &k);
    
    int num[k], rem[k];
    
    // Take moduli and remainders as input from the user
    for (int i = 0; i < k; i++) {
        printf("Enter modulus %d: ", i + 1);
        scanf("%d", &num[i]);
        printf("Enter remainder %d: ", i + 1);
        scanf("%d", &rem[i]);
    }
    
    // Call the Chinese Remainder Theorem function
    int x = chineseRemainderTheorem(num, rem, k);
    
    if (x != -1) {
        printf("The solution is %d\n", x);
    } else {
        printf("Modular inverse doesn't exist, no solution.\n");
    }

    return 0;
}