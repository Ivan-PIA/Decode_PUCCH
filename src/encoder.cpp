#include "../include/encoder.h"



void encode_PUCCH(const std::vector<int8_t>& d, std::vector<int8_t>& output) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < RATE; j++) {
            output[i] ^= (G[i][j] & d[j]);  
        }
    }
}

void encode_PUCCH_split(const std::span<const int8_t> &d, std::vector<int8_t> &output) {    
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < RATE; j++) {
            output[i] ^= (G[i][j] & d[j]);  
        }
    }
}



