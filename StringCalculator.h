#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void throwException(const char *message) {
    printf("Exception: %s\n", message);
}

int add(const char *numbers) {
    if (strcmp(numbers, "") == 0) return 0; // Handle empty string

    int total = 0;
    const char *delimiter = ",";
    char *token; // Tokenizer pointer

    // Check for custom delimiter
    if (strncmp(numbers, "//", 2) == 0) {
        char *newline = strchr(numbers, '\n');
        if (newline) {
            char customDelimiter[10]; // Hold the custom delimiter
            size_t delimiterLength = newline - (numbers + 2);
            strncpy(customDelimiter, numbers + 2, delimiterLength);
            customDelimiter[delimiterLength] = '\0'; // Null terminate

            delimiter = customDelimiter; // Set the new delimiter
            numbers = newline + 1; // Move past the line break
        }
    }

    // Initialize array for negative numbers
    int negatives[100] = {0};
    int negCount = 0;

    // Allocate a modifiable copy of numbers for tokenization
    char *modifiableNumbers = strdup(numbers); 
    if (modifiableNumbers == NULL) {
        throwException("Memory allocation failed");
        return 0;
    }

    // Tokenize and process the numbers
    token = strtok(modifiableNumbers, delimiter);
    while (token != NULL) {
        int n = atoi(token); // Convert to integer

        // Process the number
        if (n < 0) {
            negatives[negCount++] = n; // Store negative number
        } else if (n <= 1000) { 
            total += n; // Add to total if valid
        }

        token = strtok(NULL, delimiter); // Get the next number
    }

    // Handle negatives if any were found
    if (negCount > 0) {
        char msg[256];
        sprintf(msg, "negatives not allowed: ");
        for (int i = 0; i < negCount; i++) {
            sprintf(msg + strlen(msg), "%d%s", negatives[i], (i == negCount - 1) ? "" : ", ");
        }
        throwException(msg);
    }

    free(modifiableNumbers); // Free the allocated memory
    return total; // Return the total
}
