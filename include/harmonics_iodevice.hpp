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

#ifndef HARMONICS_IODEVICE_HPP
#define HARMONICS_IODEVICE_HPP

#include <QIODevice>

#include <QtCore/QPointF>
#include <QtCore/QVector>
#include <QLineSeries>
QT_CHARTS_USE_NAMESPACE

#include <fft.hpp>

namespace wiet_star
{

/*
 * This class operates as follows:
 * 1) Reads data from the device linked to it (e.g. the microphone).
 * 2) Performs a Fourier transform on the data read.
 * 3) Extracts the frequency of the first harmonic.
 * 4) Writes the result to the given destination.
 */
class harmonics_iodevice : public QIODevice
{
    Q_OBJECT
public:
    explicit harmonics_iodevice(QLineSeries* series, QObject *parent = nullptr);

signals:
    void new_harmonic(double const h);

protected:
    qint64 readData(char *data, qint64 maxSize) override;
    qint64 writeData(const char *data, qint64 maxSize) override;

private:
    using size_type = std::vector<sample_type>::size_type;
    using it_diff_type = std::vector<sample_type>::iterator::difference_type;

    std::vector<sample_type> buffer;
    size_type const sample_count {4096};
    double const min_freq {200};
    double const max_freq {4000};
    int const resolution {4};

    QLineSeries* series;
    QVector<QPointF> frequencies;
};

} // wiet_star    

#endif // HARMONICS_IODEVICE_HPP
