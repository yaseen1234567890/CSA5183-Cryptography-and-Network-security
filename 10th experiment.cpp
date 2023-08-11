#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>



void sha1_transform(uint32_t state[5], const uint8_t buffer[SHA1_BLOCK_SIZE]) {
    uint32_t a, b, c, d, e, temp;
    uint32_t m[80];

    
    for (int i = 0; i < 16; i++) {
        m[i] = (buffer[i * 4] << 24) | (buffer[i * 4 + 1] << 16) | (buffer[i * 4 + 2] << 8) | buffer[i * 4 + 3]; 
    }

    
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    for (int i = 16; i < 80; i++) {
        m[i] = SHA1_ROTL(1, m[i - 3] ^ m[i - 8] ^ m[i - 14] ^ m[i - 16]);
    }

    for (int i = 0; i < 80; i++) {
        if (i < 20) {
            temp = SHA1_ROTL(5, a) + ((b & c) | (~b & d)) + e + m[i] + 0x5A827999;
        } else if (i < 40) {
            temp = SHA1_ROTL(5, a) + (b ^ c ^ d) + e + m[i] + 0x6ED9EBA1;
        } else if (i < 60) {
            temp = SHA1_ROTL(5, a) + ((b & c) | (b & d) | (c & d)) + e + m[i] + 0x8F1BBCDC;
        } else {
            temp = SHA1_ROTL(5, a) + (b ^ c ^ d) + e + m[i] + 0xCA62C1D6;
        }

        e = d;
        d = c;
        c = SHA1_ROTL(30, b);
        b = a;
        a = temp;
    }

    // Update the state with the final values
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
}

void sha1_hash(const uint8_t *message, size_t length, uint8_t hash[20]) {
    uint32_t state[5] = {
        0x67452301,
        0xEFCDAB89,
        0x98BADCFE,
        0x10325476,
        0xC3D2E1F0
    };

    size_t index = 0;
    size_t paddingLength = 0;
    uint64_t messageLength = length * 8;
    while (length >= SHA1_BLOCK_SIZE) {
        sha1_transform(state, &message[index]);
        index += SHA1_BLOCK_SIZE;
        length -= SHA1_BLOCK_SIZE;
    }

    
    if (paddingLength > 8) {
    
        sha1_transform(state, &message[index]);
        memset(&message[index], 0, SHA1_BLOCK_SIZE);
    }

    
    for (int i = 0; i < 8; i++) {
        message[index + SHA1_BLOCK_SIZE - 8 + i] = (messageLength >> (56 - i * 8)) & 0xFF;
    }

    
    sha1_transform(state, &message[index]);

    
    for (int i = 0; i < 5; i++) {
        hash[i * 4] = (state[i] >> 24) & 0xFF;
        hash[i * 4 + 1] = (state[i] >> 16) & 0xFF;
        hash[i * 4 + 2] = (state[i] >> 8) & 0xFF;
        hash[i * 4 + 3] = state[i] & 0xFF;
    }
}

int main() {
    char input[] = "Hello, SHA-1!";
    uint8_t hash[20];

    sha1_hash((uint8_t *)input, strlen(input), hash);

    printf("Input: %s\n", input);
    printf("SHA-1 Hash: ");
    for (int i = 0; i < 20; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}

