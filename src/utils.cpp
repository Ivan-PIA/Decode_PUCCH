#include "../include/utils.h"


void generate_rand_bit(std::vector<int8_t> &bit){
    for(int i = 0; i < bit.size(); i++){
        bit[i] = rand() % 2;
    }
}

std::vector<double> count_BER(const std::vector<int8_t> &input_data, int count_snr){

    std::vector<double> ber;
    for(int snr = 0; snr < count_snr; snr++){
        std::vector<int8_t> decode_bit = split_vector(input_data,snr);
        double err = check_error(input_data,decode_bit);
        ber.push_back(err);
        printf("SNR: %d\n", snr);
    }
    return ber;
}


std::vector<int8_t> split_vector(const std::vector<int8_t> &input_data, int snr) { // Передаём по ссылке
    
    std::span<const int8_t> input_span{input_data}; // Создаём span из вектора
    
    std::vector<int8_t> decoded_full;

    for(int i = 0; i < input_data.size() / RATE; i++) {    

        std::vector<int8_t> encoded(ROW,0);
        std::vector<int8_t> decoded(RATE,0);
        std::span<const int8_t> sub_span = input_span.subspan(i * RATE, RATE);   

        encode_PUCCH_split(sub_span, encoded);
        // for(int f = 0; f < ROW; f++){
        //     printf("%d ", encoded[f]);
        // }
        // printf("\n\n");
        double disp = snr_to_dispersion(snr);
        std::vector<double> received = add_awgn_noise_bpsk(encoded, disp);
        decode_PUCCH_LLR_split(received,decoded,disp);
        // for(int f = 0; f < RATE; f++){
        //     printf("%d ", decoded[f]);
        // }
        // printf("\n\n");
        decoded_full.insert(decoded_full.end(), decoded.begin(), decoded.end());

    }   

    return decoded_full;
}


void save_to_file(const std::vector<double>& data, const char *filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "ошибка файла!" << filename << std::endl;
        return;
    }
    file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(double));
    file.close();
}


double snr_to_dispersion(double snr_dB){
    double snr_linear = pow(10.0, snr_dB / 10.0);
    double disp = sqrt(1.0 / (snr_linear));
    return disp;
}

double check_error(const std::vector<int8_t>& input, const std::vector<int8_t>& output){
    double error = 0;

    for (int i = 0; i < input.size(); i++){
        if(input[i] != output[i]){
            error++;
        }
    }

    return error/double(input.size());
}



std::vector<double> orcestator(const std::vector<int8_t>& input_data, const std::vector<int8_t>& encoded, int count_snr,int rate){

    std::vector<int8_t> decoded(RATE);
    std::vector<double> bers(0);

    for(int snr = 0; snr < count_snr; snr++){

        double disp = snr_to_dispersion(snr);
        std::vector<double> received = add_awgn_noise_bpsk(encoded,disp);
        decode_PUCCH_LLR(received, decoded, rate, disp);
        double ber = check_error(decoded, input_data);
        // printf("ber = %f\n", ber);

        bers.push_back(ber);
    }
    return bers;

}

