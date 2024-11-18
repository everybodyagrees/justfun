#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute GCD (Greatest Common Divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Function to compute the modular inverse (Extended Euclidean Algorithm)
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to compute modular exponentiation
long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int p, q, e, message;
    
    // Taking input for the prime numbers
    printf("Enter first prime number (p): ");
    scanf("%d", &p);
    printf("Enter second prime number (q): ");
    scanf("%d", &q);

    int n = p * q; // Calculate n = p * q
    int phi = (p - 1) * (q - 1); // Euler's Totient function

    // Taking input for public exponent 'e'
    printf("Enter public exponent (e): ");
    scanf("%d", &e);
    
    while (gcd(e, phi) != 1) {
        printf("e is not coprime with phi(n). Please enter a different value for e: ");
        scanf("%d", &e);
    }

    int d = modInverse(e, phi); // Private exponent

    // Display public and private keys
    printf("Public Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: (d = %d, n = %d)\n", d, n);

    // Taking input for the message
    printf("Enter message to encrypt (as a number): ");
    scanf("%d", &message);

    // Encryption
    long long encrypted = powerMod(message, e, n); // Encrypt the message
    printf("Encrypted Message: %lld\n", encrypted);

    // Decryption
    long long decrypted = powerMod(encrypted, d, n); // Decrypt the message
    printf("Decrypted Message: %lld\n", decrypted);

    return 0;
}
