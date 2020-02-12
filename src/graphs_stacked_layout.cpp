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

#include <graphs_stacked_layout.hpp>

#include <QChartView>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

#include <QDebug>

namespace wiet_star
{

graphs_stacked_layout::graphs_stacked_layout(QWidget *parent)
    : QStackedLayout {parent}
{
    QValueAxis* axis_x = new QValueAxis;
    axis_x->setRange(0, 100);
    axis_x->setMinorTickCount(2);

    QValueAxis* axis_y = new QValueAxis;
    axis_y->setRange(-4000, 4000);
    axis_y->setTitleText("Frequency difference");

    series = new QLineSeries;
    points.reserve(100);
    for (int i = 0; i < 100; i++)
        points.push_back(QPointF{static_cast<qreal>(i), 0});
    series->replace(points);

    QChart* chart = new QChart;
    chart->addSeries(series);
    chart->setAxisX(axis_x, series);
    chart->setAxisY(axis_y, series);
    chart->legend()->hide();

    QChartView* view = new QChartView {chart};

    capture = new audio_input_recorder {recorder_type::CAPTURE};
    microphone = new audio_input_recorder {recorder_type::MICROPHONE};

    addWidget(view);
    addWidget(capture);
    addWidget(microphone);

    connect(&timer, &QTimer::timeout, this, &graphs_stacked_layout::refresh_difference_graph);
    timer.start(35);
}

void graphs_stacked_layout::refresh_difference_graph()
{
    std::optional<double> freq1 {capture->get_last_harmonic()};
    std::optional<double> freq2 {microphone->get_last_harmonic()};

    if (!freq1)
        freq1 = 0.0;
    if (!freq2)
        freq2 = 0.0;

    // For C++20, std::shift_left could be used.
    for (int i = 0; i < 99; i++)
    {
        points[i].setY(points[i + 1].y());
        double const value = freq1.value() - freq2.value();
        points[99].setY(value);
        emit last_diff_value(std::abs(value));
    }

    series->replace(points);
}

} // wiet_star
