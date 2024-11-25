#include <stdlib.h>
#include <string.h>
#include "lmc_reader.h"

void read_lmc_file(const char* Cbuffer, long buffer_length, LMC_Context* lmc_state) {
    char buffer[1000];
    strcpy(buffer, Cbuffer);
    uint16_t i=0;
    do {i++;} while (buffer[i] != '%');
    do {i++;} while (buffer[i] != '%');
    i++;
    char* number_start = &(buffer[i]);
    uint16_t j = 0;
    while (i < buffer_length) {
        if (buffer[i] == ',') {
            buffer[i] = '\0';
            lmc_state->mailboxes[j] = (uint16_t)atoi(number_start);
            j++;
            number_start = &(buffer[i+1]);
        }
        i++;
    }
}