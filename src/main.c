#include <stdio.h>
#include <stdlib.h>

#include "lmc.h"
#include "lmc_reader.h"

#define OUTPUT_BUFFER_SIZE 100

int generate_context_from_lmc(char* filename, LMC_Context* ctx) {
    char* file_buffer = NULL;
    long buffer_length;
    FILE *lmc_file;
    lmc_file = fopen(filename, "r");

    if (lmc_file) {
        fseek(lmc_file, 0, SEEK_END);
        buffer_length = ftell(lmc_file);
        fseek(lmc_file, 0, SEEK_SET);
        file_buffer = malloc(buffer_length);
        if (file_buffer) {
            fread(file_buffer, 1, buffer_length, lmc_file);
        }
        fclose(lmc_file);
    } else {
        printf("ERROR READING FILE\n");
    }

    if (file_buffer) {
        read_lmc_file(file_buffer, buffer_length, ctx);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return -1;
    }

    char* filename = argv[1];
    uint16_t input = (uint16_t)atoi(argv[2]);

    LMC_Context context;
    uint16_t input_buffer[10];
    uint16_t output_buffer[OUTPUT_BUFFER_SIZE];
    uint16_t* obcopy = output_buffer;

    generate_context_from_lmc(filename, &context);

    init_lmc(&context,
             input_buffer, sizeof(input_buffer)/sizeof(uint16_t),
             obcopy, sizeof(output_buffer)/sizeof(uint16_t)
             );

    input_buffer[0] = input;

    uint32_t iterations = 0;
    while (!context.halted) {
        step_lmc(&context);
        iterations++;
    }
    for (int i = 0; i < (OUTPUT_BUFFER_SIZE - context.output_length); i++) {
        printf("%u\n", (uint16_t)*(output_buffer + i));
    }
#ifdef SHOW_ITERATIONS
    printf("Iterations: %d", iterations);
#endif
    return 0;
}
