#include <stdio.h>
#include <stdint.h>

typedef uint64_t Block;

 
static const int initial_permutation[64] = { /* ... */ };

// DES round keys (for simplicity, a fixed example key is used)
static const uint64_t round_keys[16] = { /* ... */ };

// Initial permutation (IP) function
Block initial_permute(Block input) {
    Block output = 0;
    for (int i = 0; i < 64; ++i) {
        int bit_position = initial_permutation[i] - 1;
        output |= ((input >> bit_position) & 1) << (63 - i);
    }
    return output;
}

// DES encryption round function
Block des_round(Block input, uint64_t round_key) {
    
    return input ^ round_key;
}

// DES encryption function
Block des_encrypt(Block input) {
    Block encrypted = initial_permute(input);

    for (int round = 0; round < 16; ++round) {
        encrypted = des_round(encrypted, round_keys[round]);
    }

    
    return encrypted;
}


int main() {
    Block plaintext;
    printf("Enter a 64-bit plaintext: ");
    scanf("%llx", &plaintext);

    Block encrypted = des_encrypt(plaintext);

    printf("Encrypted result: %llx\n", encrypted);

    return 0;
}

