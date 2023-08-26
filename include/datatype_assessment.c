#include "datatype_assessment.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lowlevel_functions.h"

void set_undefined_basic_type(extendedDataType* inputExtDataType) {
    inputExtDataType->basic = UNDEFINED_TYPE;
    inputExtDataType->representation.undefinedRepresentation = UNDEFINED;
}

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
    for (idxString = inputExtDataType->stringStartOffset; idxString < inputExtDataType->stringLength; idxString++) {
        char currChar = inputExtDataType->numberString[idxString];
        if (allLettersOrSymbols) {
            allLettersOrSymbols = !isnumber(currChar);
        }
        if (allValidHexChars) {
            allValidHexChars = contains_hex_letters(&currChar) || isnumber(currChar);
        }
        if (allNumbers) {
            allNumbers = isnumber(currChar);
        }
        if (!allLettersOrSymbols && !hasComma) {
            hasComma = (currChar == '.') || (currChar == ',');
        }
        if (!allLettersOrSymbols) {
            only1s0s = only1s0s && ((currChar == '0' || currChar == '1'));
        }
    }
    if (idxString == inputExtDataType->stringStartOffset) {
        // no loop cycles performed, probably wrong input
        set_undefined_basic_type(inputExtDataType);
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
        // TODO modality to consider 1/0 values as decimal numbers
        if (inputExtDataType->stringLength <= MAX_BITS) {
            // TODO modality to consider binary values as floating-point numbers
            inputExtDataType->basic = INTEGER_TYPE;
            inputExtDataType->representation.integerRepresentation = BINARY;
        } else {
            set_undefined_basic_type(inputExtDataType);
        }

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

void determine_sign(extendedDataType* inputExtDataType) {
    bool stringHasMinus = contains_minus_sign(inputExtDataType->numberString);
    bool stringHasPlus = contains_plus_sign(inputExtDataType->numberString);
    switch (inputExtDataType->basic) {
        case INTEGER_TYPE:
            if (stringHasMinus || stringHasPlus) {
                inputExtDataType->sign.integerSign = SIGNED;
            } else {
                inputExtDataType->sign.integerSign = UNSIGNED;
            }
            break;
        case FLOATING_TYPE:
            if (stringHasMinus) {
                inputExtDataType->sign.floatingSign = NEGATIVE;
            } else {
                inputExtDataType->sign.floatingSign = POSITIVE;
            }
            break;
            // TODO when to give unsigned char?
        default:
            inputExtDataType->sign.charSign = UNSIGNED;
            break;
    }
};

void determine_size(extendedDataType* inputExtDataType){};
void determine_value(extendedDataType* inputExtDataType) {}
void determine_complement(extendedDataType* inputExtDataType){};
void determine_minmax_range(extendedDataType* inputExtDataType){};

void parse_number_from_string(extendedDataType* inputExtDataType) {
    /* Extract useful numbers from inputExtDataType->numberString , recognizing invalid characters
    Valid number formats for integers are: 10011010010 , 1234 , Ox4D2 , 4D2, 00001234 / -1234 , -00001234
    Valid nuber formats for floatings are: -1234.1234 / 1.234E+3 / 0.1234
    */
    inputExtDataType->stringLength = string_length(inputExtDataType->numberString);
    if (inputExtDataType->stringLength == 0 || inputExtDataType->stringLength > MAX_BITS) {
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
};

void print_extended_datatype(const extendedDataType* const inputExtDataType) {
    if (inputExtDataType->stringLength == 0) {
        puts("Invalid length of extended data type to print!");
        return;
    }

    printf("String number <%s> | ", inputExtDataType->numberString);
    printf("Type: ");
    switch (inputExtDataType->basic) {
        case UNDEFINED_TYPE:
            printf("Undefined");
            break;
        case CHAR_TYPE:
            printf("Char");
            break;
        case INTEGER_TYPE:
            printf("Integer");
            printf(" - Representation: ");
            switch (inputExtDataType->representation.integerRepresentation) {
                case BINARY:
                    printf("Binary");
                    break;
                case DECIMAL_INT:
                    printf("Decimal");
                    switch (inputExtDataType->sign.integerSign) {
                        case SIGNED:
                            printf(" (signed)");
                            break;
                        case UNSIGNED:
                            printf(" (unsigned)");
                            break;
                        default:
                            break;
                    }
                    break;
                case HEXADECIMAL:
                    printf("Hexadecimal");
                    break;
                default:
                    printf("UNKNOWN");
                    break;
            }
            break;
        case FLOATING_TYPE:
            printf("Floating-point");
            printf(" - Representation: ");
            switch (inputExtDataType->representation.floatingRepresentation) {
                case DECIMAL_FLOAT:
                    printf("Decimal float");
                    break;
                case IEE754_SINGLE:
                    printf("IEE7544 Single-precision");
                    break;
                case IEE754_DOUBLE:
                    printf("IEE7544 Double-precision");
                    break;
                default:
                    printf("UNKNOWN");
                    break;
            }
            switch (inputExtDataType->sign.floatingSign) {
                case POSITIVE:
                    printf(" (positive)");
                    break;
                case NEGATIVE:
                    printf(" (negative)");
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    puts("");
    // TODO extend print to other characteristics
};

void closest_float_approximation(const extendedDataType* const inputExtDataType){};