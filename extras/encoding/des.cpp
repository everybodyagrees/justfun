#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int BLOCK_SIZE = 8; // Size of plaintext and ciphertext in bits
const int KEY_SIZE = 10; // Size of key in bits
const int ROUNDS = 16; // Number of rounds

struct BitArray {
    vector<bool> bits;
    
    void setBit(int index, bool value) { bits[index] = value; }
    bool getBit(int index) const { return bits[index]; }
};

// P8 permutation table
vector<int> p8_table = {6, 3, 7, 4, 1, 0, 2, 5};

// S-boxes
vector<vector<bool>> sbox = {
    {0, 1, 1, 0},
    {1, 0, 0, 1}
};

void generateSubKeys(BitArray& key) {
    BitArray l, r;
    int i;

    // Perform P10 permutation
    for (i = 0; i < BLOCK_SIZE; ++i) {
        l.bits[i] = key.bits[(i + 1) % BLOCK_SIZE];
    }

    // Split into left and right halves
    for (i = 0; i < BLOCK_SIZE / 2; ++i) {
        l.bits[i] = key.bits[i * 2];
        r.bits[i] = key.bits[i * 2 + 1];
    }

    // Perform left shift on left half
    for (i = 0; i < BLOCK_SIZE / 2; ++i) {
        l.bits[i] = l.bits[i + 1];
    }

    // Combine and perform P8 permutation
    for (i = 0; i < BLOCK_SIZE; ++i) {
        key.bits[i] = l.bits[i % (BLOCK_SIZE / 2)] ^ r.bits[i % (BLOCK_SIZE / 2)];
    }

    // Generate remaining subkeys
    for (i = 1; i < ROUNDS; ++i) {
        // Perform P8 permutation
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            key.bits[j] = key.bits[(j + 1) % BLOCK_SIZE];
        }

        // XOR with current round constant
        key.bits[BLOCK_SIZE - 1] ^= !key.bits[BLOCK_SIZE - 1];

        // Update left and right halves
        for (int j = 0; j < BLOCK_SIZE / 2; ++j) {
            l.bits[j] = key.bits[j * 2];
            r.bits[j] = key.bits[j * 2 + 1];
        }

        // Perform left shift on left half
        for (int j = 0; j < BLOCK_SIZE / 2; ++j) {
            l.bits[j] = l.bits[j + 1];
        }

        // Combine and perform P8 permutation again
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            key.bits[j] = l.bits[j % (BLOCK_SIZE / 2)] ^ r.bits[j % (BLOCK_SIZE / 2)];
        }
    }
}

BitArray encrypt(const BitArray& plaintext, const BitArray& key) {
    BitArray ciphertext = plaintext;
    BitArray L, R;

    // First round
    L = ciphertext;
    R = ciphertext;
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        L.bits[i] = ciphertext.bits[i];
        R.bits[i] = ciphertext.bits[i + 1];
    }

    // Apply S-box
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        L.bits[i] = sbox[L.bits[i]];
        R.bits[i] = sbox[R.bits[i]];
    }

    // Apply P4 permutation
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        ciphertext.bits[i] = L.bits[i % (BLOCK_SIZE / 2)] ^ R.bits[i % (BLOCK_SIZE / 2)];
    }

    // Remaining rounds
    for (int i = 1; i < ROUNDS; ++i) {
        // Expand right half
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            L.bits[j] = R.bits[j];
        }

        // XOR with subkey
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            L.bits[j] ^= key.bits[(ROUNDS - 1 - i) * BLOCK_SIZE + j];
        }

        // Apply S-box
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            L.bits[j] = sbox[L.bits[j]];
        }

        // Apply P4 permutation
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            ciphertext.bits[j] = L.bits[j % (BLOCK_SIZE / 2)] ^ R.bits[j % (BLOCK_SIZE / 2)];
        }

        // Prepare for next round
        R = L;
    }

    return ciphertext;
}

BitArray decrypt(const BitArray& ciphertext, const BitArray& key) {
    BitArray plaintext = ciphertext;
    BitArray L, R;

    // First round
    L = plaintext;
    R = plaintext;
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        L.bits[i] = plaintext.bits[i];
        R.bits[i] = plaintext.bits[i + 1];
    }

    // Apply inverse S-box
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        L.bits[i] = !L.bits[i];
        R.bits[i] = !R.bits[i];
    }

    // Apply inverse P4 permutation
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        plaintext.bits[i] = L.bits[i % (BLOCK_SIZE / 2)] ^ R.bits[i % (BLOCK_SIZE / 2)];
    }

    // Remaining rounds
    for (int i = ROUNDS - 2; i >= 1; --i) {
        // Expand right half
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            L.bits[j] = R.bits[j];
        }

        // XOR with subkey
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            L.bits[j] ^= key.bits[(ROUNDS - 1 - i) * BLOCK_SIZE + j];
        }

        // Apply inverse S-box
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            L.bits[j] = !L.bits[j];
            R.bits[j] = !R.bits[j];
        }

        // Apply inverse P4 permutation
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            plaintext.bits[j] = L.bits[j % (BLOCK_SIZE / 2)] ^ R.bits[j % (BLOCK_SIZE / 2)];
        }

        // Prepare for next round
        R = L;
    }

    return plaintext;
}

int main() {
    BitArray plaintext, ciphertext, key;
    int choice;

    cout << "Enter plaintext (8 bits): ";
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        cin >> plaintext.bits[i];
    }

    cout << "Enter key (10 bits): ";
    for (int i = 0; i < KEY_SIZE; ++i) {
        cin >> key.bits[i];
    }

    generateSubKeys(key);

    cout << "Do you want to encrypt (e), decrypt (d), or exit (x)? ";
    cin >> choice;

    switch (choice) {
        case 'e': {
            ciphertext = encrypt(plaintext, key);
            cout << "Ciphertext: ";
            for (int i = 0; i < BLOCK_SIZE; ++i) {
                cout << ciphertext.bits[i];
            }
            break;
        }
        case 'd': {
            plaintext = decrypt(ciphertext, key);
            cout << "Plaintext: ";
            for (int i = 0; i < BLOCK_SIZE; ++i) {
                cout << plaintext.bits[i];
            }
            break;
        }
        case 'x': {
            cout << "Exiting." << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Exiting." << endl;
            return 0;
        }
    }

    return 0;
}
