#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "../include/channel.h"
#include "../include/decoder.h"
#include "../include/encoder.h"
#include "matrix.h"



void generate_rand_bit(std::vector<int8_t> &bit);

std::vector<double> count_BER(const std::vector<int8_t> &input_data, int count_snr);

std::vector<int8_t> split_vector(const std::vector<int8_t> &input_data, int snr);


void save_to_file(const std::vector<double>& data, const char *filename);

double snr_to_dispersion(double snr_dB);

double check_error(const std::vector<int8_t>& input, const std::vector<int8_t>& output);

std::vector<double> orcestator(const std::vector<int8_t>& input_data, const std::vector<int8_t>& encoded, int count_snr,int rate);

#endif