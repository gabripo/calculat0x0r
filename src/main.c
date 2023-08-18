#include <stdio.h>

void print_function_inputs(int *argc, char const *argv[]) {
    if (*argc == 1) {
        // First argument is the function name
        puts("No function inputs! Returning...");
    } else {
        int inputIndex = 1;
        puts("Function inputs are:");
        while (inputIndex < *argc) {
            printf("%i-th : %s\n", inputIndex, argv[inputIndex]);
            inputIndex++;
        }
    }
}

int main(int argc, char const *argv[]) {
    puts("CALCULAT0X0R - Your travel companion to good code.");
    puts("Usage: provide numbers to process as argument of the calling executable\n");

    print_function_inputs(&argc, argv);

    return 0;
}
