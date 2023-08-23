#include <stdio.h>

#include "datatype_assessment.c"  // for clang compiler, .c instead of .h
#include "lowlevel_functions.c"

const unsigned int offset1stArg = 1;

void print_function_inputs(unsigned int *numFunctionArgs, char const *argv[]) {
    if (*numFunctionArgs == 0) {
        puts("No function inputs!");
    } else {
        unsigned int inputIndex = offset1stArg;
        puts("Function inputs are:");
        while (inputIndex < *numFunctionArgs + offset1stArg) {
            printf("%i-th : %s\n", inputIndex, argv[inputIndex]);
            inputIndex++;
        }
    }
}

int main(int argc, char const *argv[]) {
    puts("CALCULAT0X0R - Your travel companion to good code.");
    puts("Usage: provide numbers to process as argument of the calling executable.\n");

    unsigned int numFunctionArgs = argc - 1;
    print_function_inputs(&numFunctionArgs, argv);

    extendedDataType extDataTypes[numFunctionArgs];
    if (sizeof(extDataTypes) == 0) {
        puts("No function inputs, skipping creation of extended data types.");
    } else {
        for (unsigned int i = offset1stArg; i < numFunctionArgs + offset1stArg; i++) {
            if (string_length(argv[i]) > 0) {
                initialize_extended_datatype(&extDataTypes[i - offset1stArg], argv[i]);
                print_extended_datatype(&extDataTypes[i - offset1stArg]);
            }
        }
    }

    return 0;
}
