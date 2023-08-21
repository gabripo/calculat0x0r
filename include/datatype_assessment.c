#include "datatype_assessment.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lowlevel_functions.h"

void determine_numberstring_offset(extendedDataType* inputExtDataType) {
    if (contains_0x_start(inputExtDataType->numberString) || contains_0b_start(inputExtDataType->numberString)) {
        inputExtDataType->stringStartOffset = 2;
    } else if (contains_minus_sign(inputExtDataType->numberString)) {
        inputExtDataType->stringStartOffset = 1;
    } else {
        inputExtDataType->stringStartOffset = 0;
    }
}

void determine_basic_type_representation(extendedDataType* inputExtDataType) {
    bool allLettersOrSymbols = true;
    bool allValidHexChars = true;
    bool allNumbers = true;
    bool hasComma = false;
    bool only1s0s = true;
    determine_numberstring_offset(inputExtDataType);
    size_t idxString;
    for (idxString = inputExtDataType->stringStartOffset; idxString < string_length(inputExtDataType->numberString); idxString++) {
        char currChar = inputExtDataType->numberString[idxString];
        if (allLettersOrSymbols) {
            allLettersOrSymbols = !isnumber(currChar);
        }
        allValidHexChars = allValidHexChars && (contains_hex_letters(&currChar) || isnumber(currChar));
        allNumbers = allNumbers && isnumber(currChar);
        if (!allLettersOrSymbols && !hasComma) {
            hasComma = (currChar == '.') || (currChar == ',');
        }
        if (allNumbers) {
            only1s0s = only1s0s && ((currChar == '0' || currChar == '1'));
        }
    }
    if (idxString == inputExtDataType->stringStartOffset) {
        // no loop cycles performed, probably wrong input
        inputExtDataType->basic = UNDEFINED_TYPE;
        inputExtDataType->representation.undefinedRepresentation = UNDEFINED;
        return;
    }

    if (allLettersOrSymbols) {
        if (allValidHexChars) {
            // hex value with only letters
            inputExtDataType->basic = INTEGER_TYPE;
            inputExtDataType->representation.integerRepresentation = HEXADECIMAL;
        } else {
            inputExtDataType->basic = CHAR_TYPE;
        }
    } else if (hasComma) {
        inputExtDataType->basic = FLOATING_TYPE;
        inputExtDataType->representation.floatingRepresentation = DECIMAL_FLOAT;
    } else if (only1s0s) {
        // TODO modality to consider binary values as floating-point numbers
        inputExtDataType->basic = INTEGER_TYPE;
        inputExtDataType->representation.integerRepresentation = BINARY;
    } else if (allValidHexChars) {
        inputExtDataType->basic = INTEGER_TYPE;
        if (allNumbers && !contains_0x_start(inputExtDataType->numberString)) {
            inputExtDataType->representation.integerRepresentation = DECIMAL_INT;
        } else {
            inputExtDataType->representation.integerRepresentation = HEXADECIMAL;
        }
    } else {
        inputExtDataType->basic = CHAR_TYPE;
    }
};
void determine_width(extendedDataType* inputExtDataType){};
void determine_sign(extendedDataType* inputExtDataType){
    // TODO: check basic type, then the very first character, if '-'
};
void determine_size(extendedDataType* inputExtDataType){};
void determine_value(extendedDataType* inputExtDataType){};
void determine_complement(extendedDataType* inputExtDataType){};
void determine_minmax_range(extendedDataType* inputExtDataType){};

void parse_number_from_string(extendedDataType* inputExtDataType) {
    /* Extract useful numbers from inputExtDataType->numberString , recognizing invalid characters
    Valid number formats for integers are: 10011010010 , 1234 , Ox4D2 , 4D2, 00001234 / -1234 , -00001234
    Valid nuber formats for floatings are: -1234.1234 / 1.234E+3 / 0.1234
    */
    size_t numberStringLength = string_length(inputExtDataType->numberString);
    if (numberStringLength == 0) {
        return;
    }
    // TODO recognize scientific notation, case with E - rearrange string?
    determine_basic_type_representation(inputExtDataType);
    determine_width(inputExtDataType);
    determine_sign(inputExtDataType);
    determine_size(inputExtDataType);
    determine_value(inputExtDataType);
};

void initialize_extended_datatype(extendedDataType* inputExtDataType, const char* const stringToParse) {
    inputExtDataType->numberString = create_copy_string(stringToParse);
    parse_number_from_string(inputExtDataType);

    determine_complement(inputExtDataType);
    determine_minmax_range(inputExtDataType);
}