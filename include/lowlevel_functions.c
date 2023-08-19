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
