#include <stdio.h>
#include "lmc.h"
#include <stdbool.h>

#define OUTPUT_BUFFER_SIZE 100

void generate_combinations(uint16_t *array, int n, int position) {
    bool loop = true;
    while (loop) {
        // for (int j = 0; j < n; j++) {
        //     printf("%u ", array[j]);
        // }
        // printf("\n");
        // test();
        array[0] += 1;
        for (int i = 0; i < n; i++) {
            if (array[i] == 1000) {
                array[i] = 0;
                if (i == n-1) {loop=false;break;}
                if (i == 1) {
                    for (int j = 0; j < n; j++) {
                        printf("%u ", array[j]);
                    }
                    printf("\n");
                }
                array[i+1] += 1;
            }
        }
    }
}


int step_lmc_sol(LMC_Context* lmc_state) {
    uint16_t instruction;
    uint8_t opcode, operand;

    instruction = lmc_state->mailboxes[lmc_state->program_counter];
    lmc_state->program_counter++;

    opcode = instruction / 100;
    operand = instruction % 100;

    switch (opcode) {
        case 0: // HALT
            lmc_state->halted = true;
            return 2;
        case 1: // ADD
            lmc_state->accumulator += lmc_state->mailboxes[operand] % 1000;
            break;
        case 2: // SUBTRACT
            if (lmc_state->mailboxes[operand] > lmc_state->accumulator) {
                lmc_state->neg_flag = true;
            } else {
                lmc_state->neg_flag = false;
            }
            lmc_state->accumulator -= lmc_state->mailboxes[operand] % 1000;
            break;
        case 3: // STORE
            lmc_state->mailboxes[operand] = lmc_state->accumulator;
            break;
        case 5: // LOAD
            lmc_state->accumulator = lmc_state->mailboxes[operand];
            break;
        case 6: // BRANCH ALWAYS
            lmc_state->program_counter = operand;
            break;
        case 7: // BRANCH ON ZERO
            if (lmc_state->accumulator == 0) {
                lmc_state->program_counter = operand;
            }
            break;
        case 8: // BRANCH ON POSITIVE (or equal to 0)
            if (!lmc_state->neg_flag) {
                lmc_state->program_counter = operand;
            }
            break;
        case 9: // INPUT/OUTPUT
            if (operand == 01) {
                // INPUT
                lmc_state->accumulator = *(lmc_state->input_buffer);
            } else if (operand == 02) {
                // OUTPUT
                *(lmc_state->output_buffer) = lmc_state->accumulator;
                return 1;
            } else {
                // ! INVALID
                return -1;
            }
            break;
        default:
            // ! INVALID
            return -1;
    }
    return 0;
}

uint16_t get_next_collatz(const uint16_t n) {
    if (n == 0) { return -1; }
    if (n == 1) { return -1; }
    if (n % 2 == 0) {
        return n / 2;
    }
    if ((3 * n + 1) / 2 > 999) {
        return 0;
    }
    return (3 * n + 1) / 2;
}

bool test_case(LMC_Context* ctx, uint16_t test_case) {
    uint32_t iterations = 0;
    ctx->input_buffer[0] = test_case;
    uint32_t expected_output = test_case;

    while (!ctx->halted) {
        const int res = step_lmc_sol(ctx);
        if (res == 1) {
            const uint16_t out = *(ctx->output_buffer);
            if (out != expected_output) { return false; }

            expected_output = get_next_collatz(expected_output);
        } else if (res == 2) {
            if (expected_output == -1) {
                return true;
            }
            return false;
        }
        iterations++;
    }
    return true;
}

bool is_valid(LMC_Context* ctx) {
    uint16_t input_buffer[10];
    uint16_t output_buffer[OUTPUT_BUFFER_SIZE];
    uint16_t* obcopy = output_buffer;

    init_lmc(ctx,
             input_buffer, sizeof(input_buffer)/sizeof(uint16_t),
             obcopy, sizeof(output_buffer)/sizeof(uint16_t)
             );

    for (uint16_t i = 0; i < 999; i++) {
        if (!test_case(ctx, i)) {
            return false;
        }
    }
    return true;

}

int main() {
    uint16_t state[100];
    for (int i=0; i < 100; i++) {
        state[i] = 0;
    }

    generate_combinations(state, 100, 0);

    LMC_Context ctx;

    is_valid(&ctx);
}

