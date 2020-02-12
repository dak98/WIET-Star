/*
  Copyright 2020 Jakub Czajka
  Copyright (C) 2016 The Qt Company Ltd.

  This file is part of WietStar.

  WietStar is free software: you can redistribute it and/or modify it under the
  terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 3 of the License, or (at your option) any
  later version.

  WietStar is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  WietStar. If not, see <https://www.gnu.org/licenses/>.
*/

#include <harmonics_iodevice.hpp>

#include <algorithm>

#include <num_range.hpp>

#include <QDebug>

namespace wiet_star
{

harmonics_iodevice::harmonics_iodevice(QLineSeries* series, QObject *parent)
    : QIODevice {parent},
      series {series}
{}

qint64 harmonics_iodevice::readData(char *data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

qint64 harmonics_iodevice::writeData(const char *data, qint64 maxSize)
{
    if (frequencies.empty())
    {
        frequencies.reserve(100);
        for (int i = 0; i < 100; i++)
            frequencies.push_back(QPointF(i, 0));
    }

    size_type const available_samples = static_cast<size_type>(maxSize) / resolution;

    if (buffer.empty())
    {
        buffer.reserve(sample_count);
        std::fill_n(std::back_inserter(buffer), sample_count, 0);
    }

    size_type start = 0;
    /*
     * Make space for the new samples in the buffer by shifting the current
     * ones to the left.
     */
    if (available_samples < sample_count)
    {
        start = sample_count - available_samples;

        // For C++20, std::shift_left could be used.
        for (auto s : num_range<size_type>{0, start})
            buffer[s] = std::move(buffer[s + available_samples]);
    }

    for (size_type s = start; s < sample_count; ++s, data += resolution)
        buffer[s] = qreal(uchar(*data) - 128) / qreal(128);

    std::vector<sample_type> buffer_copy(buffer);
    fft(buffer_copy);

    static double const freq_step = 12000.0 / sample_count;

    static int const min_freq_pos = static_cast<int>(std::ceil(min_freq / freq_step));
    static int const max_freq_pos = static_cast<int>(std::floor(max_freq / freq_step));

    auto min_freq_it = std::begin(buffer_copy);
    auto max_freq_it = std::begin(buffer_copy);
    std::advance(min_freq_it, min_freq_pos);
    std::advance(max_freq_it, max_freq_pos);
    auto max_amplitude = std::max_element(min_freq_it, max_freq_it, [](sample_type const& a, sample_type const& b)
    {
        return std::abs(a) < std::abs(b);
    });

    it_diff_type const max_amplitude_index = std::distance(std::begin(buffer_copy), max_amplitude);
    double const harmonic = max_amplitude_index * freq_step;

    for (int i = 0; i < 99; i++)
        frequencies[i].setY(frequencies[i + 1].y());
    frequencies[99].setY(harmonic);
    series->replace(frequencies);

    emit new_harmonic(harmonic);
    
    return static_cast<int>(sample_count - start) * resolution;
}

} // wiet_star
