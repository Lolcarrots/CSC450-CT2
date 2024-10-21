#include <cstring>
#include <iostream>
#include <cstdlib>

char* readLine() {
    // Initial buffer size of 64
    size_t size = 64, length = 0;
    char* buffer = (char*)malloc(size);
    if (!buffer) {
        std::cerr << "Memory error encountered!";
        return nullptr;
    }
    int currentChar;
    // Pressing Enter means that string has been fully entered
    while ((currentChar = getchar()) != '\n' && currentChar != EOF) {
        if (length + 1 >= size) {
            // Doubles the buffer size when the current buffer size is not enough
            char* resizedBuffer = (char*)realloc(buffer, size *= 2);
            if (!resizedBuffer) {
                // Freeing up the original buffer's memory
                free(buffer);
                std::cerr << "Memory error encountered!";
                return nullptr;
            }
            // Making the resized buffer the primary buffer
            buffer = resizedBuffer;
        }
        // Handling non-ASCII characters
        if (currentChar >= 0 && currentChar <= 127) {
            buffer[length] = static_cast<char>(currentChar);
        } else {
            // Replacing all non-ASCII characters with question marks
            buffer[length] = '?';
        }
        length++;
    }
    // Preventing null termination problems
    buffer[length] = '\0';
    return buffer;
}

int main() {
    for (int count = 1; count <= 3;) {
        std::cout << "First string (Press Enter after input): ";
        char* firstString = readLine();
        if (!firstString) {
            std::cerr << "A problem occurred. Please retry.";
            // Retrying entry
            continue;
        }
        std::cout << "Second string (Press Enter after input): ";
        char* secondString = readLine();
        if (!secondString) {
            std::cerr << "A problem occurred. Please retry.";
            // Freeing up memory
            free(firstString);
            // Retrying entry
            continue;
        }
        // Determining the correct size for the concatenated string's buffer
        size_t concatenatedLength = strlen(firstString) + strlen(secondString) + 1;
        char* concatenatedString = (char*)realloc(firstString, concatenatedLength);
        if (!concatenatedString) {
            std::cerr << "Memory error encountered! Please retry.";
            // Freeing up memory for both strings
            free(firstString);
            free(secondString);
            // Retrying entry
            continue;
        }
        // Making firstString the concatenated string
        firstString = concatenatedString;

        // Concatenating the strings before printing
        strcat(firstString, secondString);

        // Printing the concatenated output
        std::cout << "Concatenated output " << count << ": " << firstString << std::endl;

        // Freeing the memory allocated to the strings
        free(firstString);
        free(secondString);
        // Increasing the count to indicate this input pair has been successful
        ++count;
    }
    return 0;
}