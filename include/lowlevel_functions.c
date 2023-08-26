#include "lowlevel_functions.h"

size_t string_length(const char* const inputString) {
    unsigned int strLength = 0;
    for (strLength = 0; inputString[strLength] != '\0'; strLength++)
        ;
    return strLength;
}

char* create_copy_string(const char* const sourceString) {
    size_t sourceLength = string_length(sourceString);
    if (sourceLength != 0) {
        char* destinationString = (char*)malloc(sourceLength + 1);

        if (destinationString) {
            memcpy(destinationString, sourceString, sourceLength + 1);
        }
        return destinationString;
    };
    return NULL;
}

bool contains_0x_start(const char* const inputString) {
    if (string_length(inputString) >= 2) {
        if ((inputString[0]) == '0' && (inputString[1] == 'x')) {
            return true;
        }
    }
    return false;
}

bool contains_0b_start(const char* const inputString) {
    if (string_length(inputString) >= 2) {
        if ((inputString[0]) == '0' && (inputString[1] == 'b')) {
            return true;
        }
    }
    return false;
}

bool contains_plus_sign(const char* const inputString) {
    if (string_length(inputString) >= 1) {
        return (inputString[0] == '+');
    }
    return false;
}

bool contains_minus_sign(const char* const inputString) {
    if (string_length(inputString) >= 1) {
        return (inputString[0] == '-');
    }
    return false;
}

bool contains_hex_letters(const char* const inputString) {
    unsigned int numHexLetters = strspn(inputString, "abcdefABCDEF");
    if (numHexLetters != 0) {
        return true;
    }
    return false;
}
