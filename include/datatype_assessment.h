#ifndef DATATYPE_ASSESSMENT
#define DATATYPE_ASSESSMENT
#include <float.h>
#include <limits.h>

#include "custom_datatypes.h"

#define MAX_BITS 64

typedef struct
{
    union {
        enum {
            BINARY,
            DECIMAL_INT,
            HEXADECIMAL
        } integerRepresentation;
        enum {
            DECIMAL_FLOAT,
            IEE754_SINGLE,
            IEE754_DOUBLE
        } floatingRepresentation;
        enum {
            UNDEFINED
        } undefinedRepresentation;
    };
} representationType;

typedef enum {
    UNDEFINED_TYPE,
    CHAR_TYPE,
    INTEGER_TYPE,
    FLOATING_TYPE
} basicType;

typedef struct {
    union {
        enum {
            SHORT,
            NORMAL,
            LONG,
            LONG_LONG,
        } integerType;
        enum {
            FLOAT,
            DOUBLE,
            LONG_DOUBLE
        } floatingType;
    };
} widthType;

typedef struct {
    union {
        enum {
            SIGNED_CHAR,
            UNSIGNED_CHAR
        } charSign;
        enum {
            SIGNED,
            UNSIGNED
        } integerSign;
        enum {
            POSITIVE,
            NEGATIVE
        } floatingSign;
    };
} signType;

typedef struct {
    union {
        enum {
            char8 = 8
        } charSize;
        enum {
            int16 = 16,
            int32 = 32,
            int64 = 64
        } integerSize;
        enum {
            float32 = 32,
            float64 = 64,
            float128 = 128
        } floatingSize;
    };
} sizeType;

typedef struct {
    basicType valueType;
    union {
        char charValue;
        schar signedCharValue;
        uchar unsignedCharValue;
        int intvalue;
        sint shortIntValue;
        usint unsignedShortIntValue;
        uint unsignedIntValue;
        lint longIntValue;
        luint longUnsignedIntValue;
        llint longLongIntValue;
        lluint longLongUnsignedIntValue;
        float floatValue;
        double doubleValue;
        ldouble longDoubleValue;
    } value;
} numValue;

typedef struct
{
    numValue min;
    numValue max;
} minMaxRange;

typedef struct
{
    char* numberString;
    size_t stringLength;
    size_t stringStartOffset;
    basicType basic;
    representationType representation;
    widthType width;
    signType sign;
    sizeType size;
    numValue value;
    numValue complement;
    minMaxRange range;
} extendedDataType;

void parse_number_from_string(extendedDataType* inputExtDataType);
void set_undefined_basic_type(extendedDataType* inputExtDataType);
void determine_numberstring_offset(extendedDataType* inputExtDataType);
void determine_basic_type_representation(extendedDataType* inputExtDataType);
void determine_width(extendedDataType* inputExtDataType);
void determine_sign(extendedDataType* inputExtDataType);
void determine_size(extendedDataType* inputExtDataType);
void determine_value(extendedDataType* inputExtDataType);
void determine_complement(extendedDataType* inputExtDataType);
void determine_minmax_range(extendedDataType* inputExtDataType);

void initialize_extended_datatype(extendedDataType* inputExtDataType, const char* const stringToParse);
// bool check_validity_extended_datatype(const extendedDataType* const inputExtDataType);
void print_extended_datatype(const extendedDataType* const dataTypeToPrint);
#endif