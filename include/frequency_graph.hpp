#ifndef WIET_STAR_FREQUENCY_GRAPH_HPP
#define WIET_STAR_FREQUENCY_GRAPH_HPP

#include <QtCharts/QChartView>

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
QT_CHARTS_USE_NAMESPACE

namespace wiet_star
{

class frequency_graph : public QChartView
{
    Q_OBJECT
public:
    frequency_graph();

private:
    QChart main_graph;
    QLineSeries main_series;
    QValueAxis x_axis, y_axis;
};

} // wiet_star

#endif // WIET_STAR_FREQUENCY_GRAPH_HPP
