#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void throwException(const char *message) {
    printf("Exception: %s\n", message);
}

const char* extractDelimiter(const char **numbers) {
    if (strncmp(*numbers, "//", 2) == 0) {
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
    }
    return ","; // Return default delimiter
}

int tokenizeAndSum(char *numbers, const char *delimiter) {
    int total = 0;
    int negatives[100] = {0};
    int negCount = 0;
    char *token = strtok(numbers, delimiter);

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

int main() {
    // Example usage
    const char *input = "//;\n1;2;3"; // Customize this input for testing
    int result = add(input);
    printf("Result: %d\n", result);
    return 0;
}
