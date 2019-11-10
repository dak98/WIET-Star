#ifndef WIET_STAR_FFT_HPP
#define WIET_STAR_FFT_HPP

#include <vector>
#include <iostream>
#include <complex>

inline std::complex<double> const i(0, 1);
inline double const PI = acos(-1);

using sample_type = std::complex<double>;
std::vector<sample_type> fft(std::vector<sample_type> data);

#endif // WIET_STAR_FFT_HPP
