#ifndef WIET_STAR_FFT_HPP
#define WIET_STAR_FFT_HPP

#include <complex>
#include <vector>

using sample_type = std::complex<double>;
void fft(std::vector<sample_type>& data);

#endif // WIET_STAR_FFT_HPP
