#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

std::vector<double> add_awgn_noise_bpsk(const std::vector<int8_t>& signal, double disper);

std::vector<double> add_awgn_noise(std::vector<int8_t>& signal, double snr_dB);

#endif 