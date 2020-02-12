/*
  Copyright 2020 Jakub Czajka

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

#include <fft.hpp>

#include <algorithm>

#include <num_range.hpp>

void fft(std::vector<sample_type>& data)
{
    static std::complex<double> constexpr i(0, 1);
    static double const PI = acos(-1);

    using size_type = std::vector<sample_type>::size_type;
    size_type const size = data.size();
    if (size > 1)
    {
        sample_type const w = std::exp(-2 * PI * i / static_cast<double>(size));
        sample_type w_k = 1.0;

        std::vector<sample_type> even;
        std::vector<sample_type> odd;
        even.reserve(size / 2);
        odd.reserve(size / 2);

        bool toggle = false;
        std::partition_copy(std::begin(data), std::end(data), std::back_inserter(even), std::back_inserter(odd), [&toggle](sample_type&)
        {
            return toggle = not toggle;
        });

        fft(even);
        fft(odd);

        for (size_type index : num_range<size_type>{0, size / 2})
        {
            sample_type const factor = w_k * odd[index];
            data[index] = even[index] + factor;
            data[index + size / 2] = even[index] - factor;
            w_k *= w;
        }
    }
}
