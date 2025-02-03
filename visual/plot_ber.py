import numpy as np
import matplotlib.pyplot as plt

def load_from_file(filename):
    with open(filename, "rb") as file:
        data = np.fromfile(file, dtype=np.float64)  
    return data


# data13 = load_from_file("ber13.bin")
# data10 = load_from_file("ber10.bin")
# data8 = load_from_file("ber8.bin")
# data2 = load_from_file("ber2.bin")

data13 = load_from_file("./file/ber13.bin")
data10 = load_from_file("./file/ber10.bin")
data7 = load_from_file("./file/ber7.bin")
data5 = load_from_file("./file/ber5.bin")
data2 = load_from_file("./file/ber2.bin")

snr = np.arange(len(data13))

plt.figure()
plt.title("BER - Decoder PUCCH F2 (BPSK)")
plt.xlabel("SNR, dB")
plt.semilogy(snr, data13, label='(20/13)')
plt.semilogy(snr, data10, label='(20/10)')
plt.semilogy(snr, data7, label='(20/7)')
plt.semilogy(snr, data5, label='(20/5)')
plt.semilogy(snr, data2, label='(20/2)')
plt.legend()
plt.show()