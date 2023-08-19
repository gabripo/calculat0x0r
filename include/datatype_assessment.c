#include "datatype_assessment.h"

#include <stdlib.h>
#include <string.h>

#include "lowlevel_functions.h"

void parse_number_from_string(extendedDataType* inputExtDataType){};
void determine_representation(extendedDataType* inputExtDataType){};
void determine_basic_type(extendedDataType* inputExtDataType){};
void determine_width(extendedDataType* inputExtDataType){};
void determine_sign(extendedDataType* inputExtDataType){};
void determine_size(extendedDataType* inputExtDataType){};
void determine_value(extendedDataType* inputExtDataType){};
void determine_complement(extendedDataType* inputExtDataType){};
void determine_minmax_range(extendedDataType* inputExtDataType){};

void initialize_extended_datatype(extendedDataType* inputExtDataType, const char* const stringToParse) {
    inputExtDataType->numberString = create_copy_string(stringToParse);
    parse_number_from_string(inputExtDataType);
    determine_representation(inputExtDataType);
    determine_basic_type(inputExtDataType);
    determine_width(inputExtDataType);
    determine_sign(inputExtDataType);
    determine_size(inputExtDataType);
    determine_value(inputExtDataType);
    determine_complement(inputExtDataType);
    determine_minmax_range(inputExtDataType);
}