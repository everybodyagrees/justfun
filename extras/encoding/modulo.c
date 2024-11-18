#include <stdio.h>

void printAdditionTable(int modulo) {
    printf("Addition Table Modulo %d:\n", modulo);
    for (int i = 0; i < modulo; i++) {  // Start from 1 instead of 0
        for (int j = 0; j < modulo; j++) {
            printf("%2d ", (i + j) % modulo);
        }
        printf("\n");
    }
}

void printMultiplicationTable(int modulo) {
    printf("\nMultiplication Table Modulo %d:\n", modulo);
    for (int i = 1; i < modulo; i++) {  // Start from 1 instead of 0
        for (int j = 1; j < modulo; j++) {
            printf("%2d ", (i * j) % modulo);
        }
        printf("\n");
    }
}

int main() {
    int modulo;
    printf("Enter the modulo value: ");
    scanf("%d", &modulo);
    
    printAdditionTable(modulo);
    printMultiplicationTable(modulo);
    
    return 0;
}
