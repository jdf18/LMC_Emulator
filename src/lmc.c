#include "lmc.h"

#include <stdio.h>

void init_lmc(LMC_Context* lmc_state, uint16_t* input_buffer, uint16_t input_length, uint16_t* output_buffer, uint16_t output_length) {
    lmc_state->accumulator = 0;
    lmc_state->program_counter = 0;
    lmc_state->input_buffer = input_buffer;
    lmc_state->input_length = input_length;
    lmc_state->output_buffer = output_buffer;
    lmc_state->output_length = output_length;
    lmc_state->halted = false;
}

int step_lmc(LMC_Context* lmc_state) {
    uint16_t instruction;
    uint8_t opcode, operand;

    instruction = lmc_state->mailboxes[lmc_state->program_counter];
    lmc_state->program_counter++;

    opcode = instruction / 100;
    operand = instruction % 100;

    switch (opcode) {
        case 0: // HALT
            lmc_state->halted = true;
            break;
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
                if (lmc_state->input_length > 0) {
                    lmc_state->accumulator = *(lmc_state->input_buffer);
                    lmc_state->input_buffer++;
                    lmc_state->input_length--;
                }
            } else if (operand == 02) {
                // OUTPUT
                if (lmc_state->output_length > 0) {
                    *(lmc_state->output_buffer) = lmc_state->accumulator;
                    lmc_state->output_buffer++;
                    lmc_state->output_length--;
                }
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