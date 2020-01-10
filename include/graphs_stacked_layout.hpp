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
