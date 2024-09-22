#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void throwException(char *message) {
    printf("Exception: %s\n", message);
}

int add(char *numbers) {
    if (strcmp(numbers, "") == 0) return 0; // Handle empty string

    int total = 0;
    char *delimiter = ",";
    char *ptr;

    // Check for custom delimiter
    if (strncmp(numbers, "//", 2) == 0) {
        char *newline = strchr(numbers, '\n');
        if (newline) {
            *newline = 0; // Temporarily end string
            delimiter = numbers + 2; // Custom delimiter after "//"
            numbers = newline + 1; // Move past the line break
        }
    }

    // Initialize array for negative numbers
    int negatives[100];
    int negCount = 0;

    // Tokenize and process the numbers
    ptr = strtok(numbers, delimiter);
    while (ptr != NULL) {
        int n = atoi(ptr); // Convert to integer

        // Process the number
        if (n < 0) {
            negatives[negCount++] = n; // Store negative number
        } else if (n <= 1000) { 
            total += n; // Add to total if valid
        }

        ptr = strtok(NULL, delimiter); // Get the next number
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

    return total; // Return the total
}
