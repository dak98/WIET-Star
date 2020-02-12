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

#ifndef AUDIO_INPUT_RECORDER_HPP
#define AUDIO_INPUT_RECORDER_HPP

#include <QChartView>

#include <QtMultimedia/QAudioInput>

#include <harmonics_iodevice.hpp>

QT_CHARTS_USE_NAMESPACE

namespace wiet_star
{

enum recorder_type
{
    MICROPHONE,
    CAPTURE
};

class audio_input_recorder : public QChartView
{
    Q_OBJECT
public:
    explicit audio_input_recorder(recorder_type type, QWidget *parent = nullptr);
    ~audio_input_recorder();

    std::optional<double> get_last_harmonic() const { return last_harmonic; }

public slots:
    void set_last_harmonic(double const h) { last_harmonic = h; }

private:
    harmonics_iodevice* io_device;
    QAudioInput* input_device;

    std::optional<double> last_harmonic;
};

} // wiet_star    

#endif // AUDIO_INPUT_RECORDER_HPP
