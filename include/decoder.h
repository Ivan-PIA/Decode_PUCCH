#ifndef DECODER_H
#define DECODER_H


#include <vector>
#include <span>
#include <stdint.h>

#include "../include/encoder.h"



void decode_PUCCH_LLR(const std::vector<double>& received, std::vector<int8_t> &decoded, int rate, double disp);

void decode_PUCCH_LLR_split(const std::vector<double>& received, std::vector<int8_t> &decoded, double disp);

void decode_PUCCH_int(std::vector<int8_t> received, std::vector<int8_t> &decoded, int rate);

void decode_PUCCH_float(std::vector<double> received, std::vector<int8_t> &decoded, int rate);

#endif 