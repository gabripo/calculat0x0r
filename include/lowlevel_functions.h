#ifndef LOW_LEVEL_FUNS
#define LOW_LEVEL_FUNS

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

const char hexLetters[] = "abcdefABCDEF";

size_t string_length(const char* const inputString);
char* create_copy_string(const char* const sourceString);
bool contains_0x_start(const char* const inputString);
bool contains_minus_sign(const char* const inputString);
bool contains_hex_letters(const char* const inputString);

#endif