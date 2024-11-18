#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to prepare the input (remove spaces, convert to uppercase, and replace J with I)
void prepare_input(char input[]) {
    int i, j = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ') {
            input[j++] = toupper(input[i]);
            if (input[j - 1] == 'J') input[j - 1] = 'I';
        }
    }
    input[j] = '\0';
}

// Function to create the 5x5 key matrix for the Playfair cipher
void create_key_matrix(char key[], char key_matrix[SIZE][SIZE]) {
    int i, j, k, flag;
    char c;

    // Initialize the matrix with zero
    memset(key_matrix, 0, SIZE * SIZE * sizeof(char));

    // Add the key to the matrix
    for (i = 0, k = 0; key[i] != '\0' && k < SIZE * SIZE; i++) {
        c = toupper(key[i]);
        if (c < 'A' || c > 'Z') continue;
        if (c == 'J') continue; // Omit 'J'

        // Check if character is already in the matrix
        for (j = 0, flag = 0; j < k; j++) {
            if (key_matrix[j / SIZE][j % SIZE] == c) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            key_matrix[k / SIZE][k % SIZE] = c;
            k++;
        }
    }

    // Fill the matrix with other letters
    for (c = 'A'; c <= 'Z' && k < SIZE * SIZE; c++) {
        if (c == 'J') continue; // Omit 'J'

        // Check if character is already in the matrix
        for (j = 0, flag = 0; j < SIZE * SIZE; j++) {
            if (key_matrix[j / SIZE][j % SIZE] == c) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            key_matrix[k / SIZE][k % SIZE] = c;
            k++;
        }
    }
}

// Function to print the key matrix
void print_key_matrix(char key_matrix[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%c ", key_matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char key[26];
    char key_matrix[SIZE][SIZE];
    char input[100];

    // Get key from user
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove trailing newline

    // Get plaintext from user
    printf("Enter plaintext: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove trailing newline

    // Prepare the input text
    prepare_input(input);
    printf("Prepared input: %s\n", input);

    // Create the key matrix
    create_key_matrix(key, key_matrix);

    // Print the key matrix
    printf("Key Matrix:\n");
    print_key_matrix(key_matrix);

    // Implement the Playfair cipher encryption here (omitted for simplicity)

    return 0;
}
