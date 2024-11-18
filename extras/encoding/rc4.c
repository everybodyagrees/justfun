#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1024  // Define a maximum size for the plaintext/ciphertext
#define SWAP(a, b) { int temp = a; a = b; b = temp; }

void rc4_init(unsigned char *key, int key_len, unsigned char *S) {
    int i, j = 0;

    // Initialize the permutation array S
    for (i = 0; i < 256; i++) {
        S[i] = i;
    }

    // Key-scheduling algorithm (KSA)
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_len]) % 256;
        SWAP(S[i], S[j]);
    }
}

void rc4_generate(unsigned char *S, unsigned char *input, unsigned char *output, int data_len) {
    int i = 0, j = 0, t;

    // Pseudo-random generation algorithm (PRGA)
    for (int k = 0; k < data_len; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        SWAP(S[i], S[j]);
        
        t = (S[i] + S[j]) % 256;
        output[k] = input[k] ^ S[t];  // XOR input with generated keystream
    }
}

int main() {
    unsigned char key[256];   // Buffer to hold the key
    unsigned char plaintext[MAX_TEXT_LENGTH];  // Buffer to hold the plaintext
    int key_len;
    
    // Get the key from the user
    printf("Enter the key: ");
    fgets((char *)key, sizeof(key), stdin);
    key_len = strlen((char *)key) - 1;  // Exclude newline character
    
    // Get the plaintext message from the user
    printf("Enter the plaintext: ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);
    int data_len = strlen((char *)plaintext) - 1;  // Exclude newline character

    unsigned char S[256];  // State array
    unsigned char ciphertext[MAX_TEXT_LENGTH];
    unsigned char decrypted[MAX_TEXT_LENGTH];

    // Initialize the RC4 cipher with the key
    rc4_init(key, key_len, S);

    // Encrypt the plaintext
    rc4_generate(S, plaintext, ciphertext, data_len);

    printf("Ciphertext: ");
    for (int i = 0; i < data_len; i++) {
        printf("%02X ", ciphertext[i]);  // Print each byte as hexadecimal
    }
    printf("\n");

    // Reinitialize S for decryption (RC4 encryption and decryption are symmetric)
    rc4_init(key, key_len, S);

    // Decrypt the ciphertext
    rc4_generate(S, ciphertext, decrypted, data_len);

    printf("Decrypted text: ");
    for (int i = 0; i < data_len; i++) {
        printf("%c", decrypted[i]);
    }
    printf("\n");

    return 0;
}
