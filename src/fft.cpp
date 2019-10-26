#include "../include/fft.hpp"

using namespace std::complex_literals;
using std::vector;
using std::complex;

vector<complex<double>> fft(vector<complex<double>> data) {
    double N = data.size();
    if (N <= 1) return data;

    complex<double> w = std::exp(-2 * PI * i / N);
    complex<double> w_k = 1.0;

    vector<complex<double>> even;
    vector<complex<double>> odd;

    for (int i = 0; i < N; i+=2) {
        even.push_back(data.at(i));
    }
    for (int i = 1; i < N; i+=2) {
        odd.push_back(data.at(i));
    }

    even = fft(even);
    odd = fft(odd);

    for (int k = 0; k < N / 2; k++) {
        data[k] = even[k] + w_k * odd[k];
        data[k + N / 2] = even[k] - w_k * odd[k];
        w_k *= w;
    }

    return data;
}
