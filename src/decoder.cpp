#include "../include/decoder.h"



// brute force - (softbit)

void decode_PUCCH_LLR(const std::vector<double>& received, std::vector<int8_t> &decoded, int rate, double disp) {
    std::vector<int8_t> best_d(rate);
    int max_score = -1;

    for (int i = 0; i < (1 << rate); i++) {
        std::vector<int8_t> candidate_d(rate);
        std::vector<int8_t> candidate_c(ROW);

        for (int j = 0; j < rate; j++) {
            candidate_d[j] = (i >> j) & 1;
        }

        encode_PUCCH(candidate_d, candidate_c);

        int score = 0;
        for (int j = 0; j < ROW; j++) {
            double llr = (2.0 * received[j]) / disp;

            int8_t decoded_bit = (llr >= 0) ? 1 : 0;
            
            if (decoded_bit == candidate_c[j]) {
                score++;
            }
        }

        if (score > max_score) {
            max_score = score;
            best_d = candidate_d;
        }
    }

    decoded = best_d;
}


void decode_PUCCH_LLR_split(const std::vector<double>& received, std::vector<int8_t> &decoded, double disp) {
    std::vector<int8_t> best_d(RATE);
    int max_score = -1;

    for (int i = 0; i < (1 << RATE); i++) {
        std::vector<int8_t> candidate_d(RATE);
        std::vector<int8_t> candidate_c(ROW);

        for (int j = 0; j < RATE; j++) {
            candidate_d[j] = (i >> j) & 1;
        }

        encode_PUCCH(candidate_d, candidate_c);

        int score = 0;
        for (int j = 0; j < ROW; j++) {
            double llr = (2.0 * received[j]) / disp;

            int8_t decoded_bit = (llr >= 0) ? 1 : 0;
            
            if (decoded_bit == candidate_c[j]) {
                score++;
            }
        }

        if (score > max_score) {
            max_score = score;
            best_d = candidate_d;
        }
    }

    decoded = best_d;
}


void decode_PUCCH_int(std::vector<int8_t> received, std::vector<int8_t> &decoded, int rate) {
    std::vector<int8_t> best_d(rate);
    int max_score = -1;

    // Перебираем все 2^13 
    for (int i = 0; i < (1 << rate); i++) {

        std::vector<int8_t> candidate_d(rate);
        std::vector<int8_t> candidate_c(ROW);

        
        for (int j = 0; j < rate; j++) {
            candidate_d[j] = (i >> j) & 1;
        }

        encode_PUCCH(candidate_d, candidate_c);

        int score = 0;
        for (int j = 0; j < ROW; j++) {
            score += (received[j] == candidate_c[j]);     
        }
        
        if (score > max_score) {
            max_score = score;
            best_d = candidate_d;
            
        }
    }
    decoded = best_d;
    
}

void decode_PUCCH_float(std::vector<double> received, std::vector<int8_t> &decoded, int rate){
    
    std::vector<int8_t> best_d(rate);
    int max_score = -1;

    // Перебираем все 2^13 
    for (int i = 0; i < (1 << rate); i++) {
        // printf("i: %d", i);
        std::vector<int8_t> candidate_d(rate);
        std::vector<int8_t> candidate_c(ROW);

        
        for (int j = 0; j < rate; j++) {
            candidate_d[j] = (i >> j) & 1;
            // printf(" %d", candidate_d[j]);
        }
        // printf("\n");
        
        encode_PUCCH(candidate_d, candidate_c);

        
        int score = 0;
        for (int j = 0; j < ROW; j++) {
            int8_t bit= 0;
            if(received[j] >= 0.5){
                bit = 1;
            }
            else{
                bit = 0;
            }
            // printf("%d ", bit);
            score += (bit == candidate_c[j]);
            // printf("(%d == %d) += %d\n", bit, candidate_c[j], score );
            // score += (static_cast<double>(received[j]) == static_cast<double>(candidate_c[j]));  
            // printf("received = candidate_c: %f = %f\n", static_cast<double>(received[j]), static_cast<double>(candidate_c[j]));   
        }
        // printf("\n");
        // printf("i: %d score: %d\n", i, score);
        
        if (score > max_score) {
            max_score = score;
            best_d = candidate_d;
            
        }
    }
    // printf("max: %d\n", max_score);
    decoded = best_d;    
}
