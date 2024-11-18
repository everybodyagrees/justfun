#include <stdio.h>

// Function to calculate gcd of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate Euler's Totient Function and print coprime values
int euler_totient(int n) {
    int result = 1;  // Start with 1 as 1 is coprime with all numbers
    
    printf("Coprime values with %d are: 1", n); // Start with 1 (since it's always coprime)
    
    for (int i = 2; i < n; i++) {
        if (gcd(i, n) == 1) {
            result++;  // Increment count if i is coprime with n
            printf(", %d", i);  // Print coprime value
        }
    }
    printf("\n");  // Move to the next line after printing all coprime values
    
    return result;
}

int main() {
    int n;
    
    printf("Enter an integer: ");
    scanf("%d", &n);
    
    printf("Euler's Totient Function value for %d is %d\n", n, euler_totient(n));
    
    return 0;
}
