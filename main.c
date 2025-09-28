#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Function prototypes from convert.c
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

#define MAX_LINE_LEN 256
#define MAX_BUFFER_LEN 128

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <test_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LEN];
    int test_count = 0;
    int passed_count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Ignore comments and empty lines
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }

        char function_name[50], input[100], expected[128];
        
        int items = sscanf(line, "%49s %99s %127s", function_name, input, expected);
        if (items != 3) {
            continue; // Skip malformed lines.
        }

        test_count++;
        char actual[MAX_BUFFER_LEN] = {0};

        // Dispatch to the correct conversion function based on the test file.
        if (strcmp(function_name, "oct_to_bin") == 0) {
            oct_to_bin(input, actual);
        } else if (strcmp(function_name, "oct_to_hex") == 0) {
            oct_to_hex(input, actual);
        } else if (strcmp(function_name, "hex_to_bin") == 0) {
            hex_to_bin(input, actual);
        } else if (strcmp(function_name, "to_sign_magnitude") == 0) {
            int32_t n = atoi(input);
            to_sign_magnitude(n, actual);
        } else if (strcmp(function_name, "to_ones_complement") == 0) {
            int32_t n = atoi(input);
            to_ones_complement(n, actual);
        } else if (strcmp(function_name, "to_twos_complement") == 0) {
            int32_t n = atol(input); // Use atol for the full 32-bit range.
            to_twos_complement(n, actual);
        }

        // Compare the actual result with the expected output and report status.
        int passed = (strcmp(actual, expected) == 0);
        if (passed) {
            passed_count++;
        }

        printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
               test_count, function_name, input, expected, actual,
               passed ? "PASS" : "FAIL");
    }

    fclose(file);

    // Print the final summary of test results.
    printf("Summary: %d/%d tests passed\n", passed_count, test_count);

    return 0;
}