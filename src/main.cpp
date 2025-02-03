#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include "../include/utils.h"
#include "../include/channel.h"
#include "../include/decoder.h"


//g++ decode_pucch.cpp -o l -std=c++20 -DRATE=20
int main() {

    // srand(time(0));
    int count_bit = RATE * 1000;

    std::vector<int8_t> input_bit(count_bit);
    std::vector<int8_t> ouput_bit(count_bit);

    generate_rand_bit(input_bit);

    std::vector<double> bers = count_BER(input_bit,15);


    char filename[20];
    sprintf(filename, "bertest%d.bin", RATE);

    save_to_file(bers,filename);

    return 0;
}