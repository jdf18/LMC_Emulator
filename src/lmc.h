#ifndef LMCEMULATOR_LMC_H
#define LMCEMULATOR_LMC_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint16_t mailboxes[100];
    uint16_t accumulator;
    uint8_t program_counter;
    bool neg_flag;
    bool halted;

    uint16_t* input_buffer;
    uint16_t input_length;
    uint16_t* output_buffer;
    uint16_t output_length;
} LMC_Context;

void init_lmc(LMC_Context* lmc_state, uint16_t* input_buffer, uint16_t input_length, uint16_t* output_buffer, uint16_t output_length);
int step_lmc(LMC_Context* lmc_state);

#endif //LMCEMULATOR_LMC_H
