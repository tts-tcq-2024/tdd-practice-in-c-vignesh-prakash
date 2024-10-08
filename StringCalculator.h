#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NEGATIVES 100
#define MSG_SIZE 256

void throwException(const char *message) {
    printf("Exception: %s\n", message);
}

void constructNegativeMessage(int *negatives, int negCount, char *msg) {
    sprintf(msg, "negatives not allowed: ");
    for (int i = 0; i < negCount; i++) {
        sprintf(msg + strlen(msg), "%d%s", negatives[i], (i == negCount - 1) ? "" : ", ");
    }
}

void handleNegatives(int *negatives, int negCount) {
    if (negCount > 0) {
        char msg[MSG_SIZE]; // Use a fixed-size buffer
        constructNegativeMessage(negatives, negCount, msg);
        throwException(msg);
    }
}

char* extractCustomDelimiter(const char **numbers) {
    const char *newline = strchr(*numbers, '\n');
    if (newline) {
        size_t delimiterLength = newline - (*numbers + 2);
        char *customDelimiter = strndup(*numbers + 2, delimiterLength);
        if (!customDelimiter) {
            throwException("Memory allocation failed");
        }
        *numbers = newline + 1; // Move past the line break
        return customDelimiter;
    }
    return NULL;
}

const char* extractDelimiter(const char **numbers) {
    if (strncmp(*numbers, "//", 2) == 0) {
        char *customDelimiter = extractCustomDelimiter(numbers);
        if (customDelimiter) {
            return customDelimiter;
        }
    }
    return ",\n"; // Add newline as a default delimiter
}

int processNumber(const char *token, int *negatives, int *negCount) {
    int n = atoi(token); // Convert to integer
    if (n < 0) {
        negatives[(*negCount)++] = n; // Store negative number
        return 0;
    }
    return (n <= 1000) ? n : 0; // Return the number if valid, else return 0
}

int tokenizeAndSum(char *numbers, const char *delimiter) {
    int total = 0;
    int negatives[MAX_NEGATIVES] = {0};
    int negCount = 0;

    char *token = strtok(numbers, delimiter);
    while (token != NULL) {
        total += processNumber(token, negatives, &negCount);
        token = strtok(NULL, delimiter); // Get the next number
    }

    handleNegatives(negatives, negCount); // Handle negatives if any were found
    return total; // Return the total
}

int add(const char *numbers) {
    if (strcmp(numbers, "") == 0) return 0; // Handle empty string

    const char *delimiterStr = numbers; // Start with original string
    char *modifiableNumbers = strdup(numbers);
    if (modifiableNumbers == NULL) {
        throwException("Memory allocation failed");
        return 0;
    }

    // Extract delimiter and adjust number string
    const char *delimiter = extractDelimiter(&delimiterStr);
    // Tokenize and sum the numbers
    int total = tokenizeAndSum(modifiableNumbers, delimiter);

    free(modifiableNumbers); // Free the allocated memory
    return total; // Return the total
}
