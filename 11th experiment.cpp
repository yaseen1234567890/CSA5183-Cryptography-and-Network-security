#include <stdio.h>
#include <stdint.h>

// Euclidean algorithm to compute the greatest common divisor (GCD)
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean algorithm to compute modular inverse
uint64_t extendedEuclidean(uint64_t a, uint64_t n) {
    uint64_t t1 = 0, t2 = 1;
    uint64_t r1 = n, r2 = a;

    while (r2 > 0) {
        uint64_t q = r1 / r2;

        uint64_t temp = r2;
        r2 = r1 - q * r2;
        r1 = temp;

        temp = t2;
        t2 = t1 - q * t2;
        t1 = temp;
    }

    if (r1 > 1) {
        printf("Inverse does not exist.\n");
        return 0; // Inverse doesn't exist
    }
    
    if (t1 < 0) {
        t1 += n;
    }

    return t1;
}

int main() {
    uint64_t a = 17;  // Number for which modular inverse is to be found
    uint64_t n = 43;  // Modulus

    // Ensure that 'a' and 'n' are coprime (gcd(a, n) = 1)
    if (gcd(a, n) != 1) {
        printf("'a' and 'n' are not coprime. Inverse does not exist.\n");
        return 1;
    }

    uint64_t inverse = extendedEuclidean(a, n);
    printf("Inverse of %llu modulo %llu is %llu\n", a, n, inverse);

    return 0;
}

