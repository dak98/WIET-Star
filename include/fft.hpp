#ifndef FFT_HPP
#define FFT_HPP

#include <vector>
#include <iostream>
#include <complex>

constexpr std::complex<double> i(0, 1);
constexpr double PI = acos(-1);

std::vector<std::complex<double>> fft(std::vector<std::complex<double>> data);

#endif // FFT_HPP
