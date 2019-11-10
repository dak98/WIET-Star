#include <fft.hpp>

std::vector<sample_type> fft(std::vector<sample_type> data)
{
    double const size = data.size();
    if (size <= 1)
        return data;

    sample_type const w = std::exp(-2 * PI * i / size);
    sample_type w_k = 1.0;

    std::vector<sample_type> even;
    std::vector<sample_type> odd;

    for (unsigned index = 0; index < size; index += 2)
        even.push_back(data[index]);

    for (unsigned index = 1; index < size; index += 2)
        odd.push_back(data[index]);

    even = fft(even);
    odd = fft(odd);

    for (unsigned index = 0; index < size / 2; index++)
    {
        data[index] = even[index] + w_k * odd[index];
        data[index + unsigned(size) / 2] = even[index] - w_k * odd[index];
        w_k *= w;
    }

    return data;
}
