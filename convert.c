#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

// Helper to convert a 32-bit unsigned int to a binary string.
void to_32bit_binary_string(uint32_t value, char *out) {
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0'; // Null-terminate the string
}

// Converts an octal string to its binary representation using 3-bit mapping.
void oct_to_bin(const char *oct, char *out) {
    int pos = 0;
    for (int i = 0; oct[i] != '\0'; i++) {
        switch (oct[i]) {
            case '0': strcpy(&out[pos], "000"); break;
            case '1': strcpy(&out[pos], "001"); break;
            case '2': strcpy(&out[pos], "010"); break;
            case '3': strcpy(&out[pos], "011"); break;
            case '4': strcpy(&out[pos], "100"); break;
            case '5': strcpy(&out[pos], "101"); break;
            case '6': strcpy(&out[pos], "110"); break;
            case '7': strcpy(&out[pos], "111"); break;
        }
        pos += 3;
    }
    out[pos] = '\0';
}

// Converts a hexadecimal string to binary using 4-bit mapping.
void hex_to_bin(const char *hex, char *out) {
    int pos = 0;
    for (int i = 0; hex[i] != '\0'; i++) {
        char c = tolower(hex[i]);
        switch (c) {
            case '0': strcpy(&out[pos], "0000"); break;
            case '1': strcpy(&out[pos], "0001"); break;
            case '2': strcpy(&out[pos], "0010"); break;
            case '3': strcpy(&out[pos], "0011"); break;
            case '4': strcpy(&out[pos], "0100"); break;
            case '5': strcpy(&out[pos], "0101"); break;
            case '6': strcpy(&out[pos], "0110"); break;
            case '7': strcpy(&out[pos], "0111"); break;
            case '8': strcpy(&out[pos], "1000"); break;
            case '9': strcpy(&out[pos], "1001"); break;
            case 'a': strcpy(&out[pos], "1010"); break;
            case 'b': strcpy(&out[pos], "1011"); break;
            case 'c': strcpy(&out[pos], "1100"); break;
            case 'd': strcpy(&out[pos], "1101"); break;
            case 'e': strcpy(&out[pos], "1110"); break;
            case 'f': strcpy(&out[pos], "1111"); break;
        }
        pos += 4;
    }
    out[pos] = '\0';
}

// Converts an octal string to hexadecimal via a binary intermediate.
void oct_to_hex(const char *oct, char *out) {
    char binary_buffer[100];
    oct_to_bin(oct, binary_buffer);

    int bin_len = strlen(binary_buffer);
    int padding = (4 - (bin_len % 4)) % 4; // Calculate needed padding for 4-bit groups.
    char padded_binary[104];

    for (int i = 0; i < padding; i++) {
        padded_binary[i] = '0';
    }
    strcpy(&padded_binary[padding], binary_buffer);

    int hex_pos = 0;
    for (int i = 0; i < strlen(padded_binary); i += 4) {
        char nibble[5];
        strncpy(nibble, &padded_binary[i], 4);
        nibble[4] = '\0';

        if (strcmp(nibble, "0000") == 0) out[hex_pos] = '0';
        else if (strcmp(nibble, "0001") == 0) out[hex_pos] = '1';
        else if (strcmp(nibble, "0010") == 0) out[hex_pos] = '2';
        else if (strcmp(nibble, "0011") == 0) out[hex_pos] = '3';
        else if (strcmp(nibble, "0100") == 0) out[hex_pos] = '4';
        else if (strcmp(nibble, "0101") == 0) out[hex_pos] = '5';
        else if (strcmp(nibble, "0110") == 0) out[hex_pos] = '6';
        else if (strcmp(nibble, "0111") == 0) out[hex_pos] = '7';
        else if (strcmp(nibble, "1000") == 0) out[hex_pos] = '8';
        else if (strcmp(nibble, "1001") == 0) out[hex_pos] = '9';
        else if (strcmp(nibble, "1010") == 0) out[hex_pos] = 'A';
        else if (strcmp(nibble, "1011") == 0) out[hex_pos] = 'B';
        else if (strcmp(nibble, "1100") == 0) out[hex_pos] = 'C';
        else if (strcmp(nibble, "1101") == 0) out[hex_pos] = 'D';
        else if (strcmp(nibble, "1110") == 0) out[hex_pos] = 'E';
        else if (strcmp(nibble, "1111") == 0) out[hex_pos] = 'F';
        hex_pos++;
    }
    out[hex_pos] = '\0';

    // If the string is longer than 1 char and starts with '0', remove it.
    if (strlen(out) > 1 && out[0] == '0') {
        memmove(out, out + 1, strlen(out));
    }
}

// Converts a signed 32-bit int to its sign-magnitude representation.
void to_sign_magnitude(int32_t n, char *out) {
    uint32_t magnitude = (n < 0) ? -n : n;
    to_32bit_binary_string(magnitude, out);
    if (n < 0) {
        out[0] = '1'; // Set the sign bit for a negative number.
    }
}

// Converts a signed 32-bit int to its one's complement representation.
void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary_string(n, out);
    } else {
        uint32_t magnitude = -n;
        to_32bit_binary_string(magnitude, out);
        // For negative numbers, flip all the bits.
        for (int i = 0; i < 32; i++) {
            out[i] = (out[i] == '0') ? '1' : '0';
        }
    }
}

// Converts a signed 32-bit int to its two's complement representation.
void to_twos_complement(int32_t n, char *out) {
    // C's signed-to-unsigned cast naturally produces the two's complement bit pattern.
    uint32_t bit_pattern = (uint32_t)n;
    to_32bit_binary_string(bit_pattern, out);
}