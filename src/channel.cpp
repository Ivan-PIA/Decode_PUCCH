#include "../include/channel.h"


std::vector<double> add_awgn_noise_bpsk(const std::vector<int8_t>& signal, double disper) {
    int N = signal.size();
    std::vector<double> noisy_signal(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> gauss_dist(0.0, disper);

    for (int i = 0; i < N; i++) {
        double bpsk_signal = (signal[i] == 0) ? -1.0 : 1.0;
        noisy_signal[i] = bpsk_signal + gauss_dist(gen);
    }

    return noisy_signal;
}



std::vector<double> add_awgn_noise(std::vector<int8_t>& signal, double snr_dB) {
    int N = signal.size();
    std::vector<double> noisy_signal(N);

    double snr_linear = pow(10.0, snr_dB / 10.0);

    double noise_stddev = sqrt(1.0 / (2.0 * snr_linear));

    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::normal_distribution<double> gauss_dist(0.0, noise_stddev);

    for (int i = 0; i < N; i++) {
        noisy_signal[i] = static_cast<double>(signal[i]) + gauss_dist(gen);
    }

    return noisy_signal;
}
