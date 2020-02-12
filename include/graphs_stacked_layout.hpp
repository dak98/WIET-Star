/*
  Copyright 2020 Jakub Czajka

  This file is part of WietStar.

  WietStar is free software: you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or (at your option) any later
  version.

  WietStar is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  WietStar. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef GRAPHS_STACKED_LAYOUT_HPP
#define GRAPHS_STACKED_LAYOUT_HPP

#include <QStackedLayout>

#include <QLineSeries>
#include <QPointF>
#include <QTimer>
#include <QVector>

#include <audio_input_recorder.hpp>

namespace wiet_star
{

class graphs_stacked_layout : public QStackedLayout
{
    Q_OBJECT

public:
    graphs_stacked_layout(QWidget *parent = nullptr);

signals:
    void last_diff_value(double const v);

public slots:
    void refresh_difference_graph();

private:
    audio_input_recorder* capture;
    audio_input_recorder* microphone;

    QLineSeries* series;
    QVector<QPointF> points;

    QTimer timer;
};

} // wiet_star

#endif // GRAPHS_STACKED_LAYOUT_HPP
