#ifndef ENCODER_H
#define ENCODER_H

#include <vector>
#include <span>
#include <stdint.h>
#include "matrix.h" 

void encode_PUCCH(const std::vector<int8_t>& d, std::vector<int8_t>& output);
void encode_PUCCH_split(const std::span<const int8_t>& d, std::vector<int8_t>& output);

#endif 