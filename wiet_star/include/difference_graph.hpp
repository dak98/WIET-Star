#ifndef DIFFERENCE_GRAPH_HPP
#define DIFFERENCE_GRAPH_HPP

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QProcess>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

#include <boost/interprocess/managed_shared_memory.hpp>
namespace bip = boost::interprocess;
using shm = bip::managed_shared_memory;

namespace wiet_star
{

class difference_graph : public QChartView
{
    Q_OBJECT

public:
    difference_graph(QWidget *parent = nullptr);
    ~difference_graph();

signals:
    void last_diff_value(double const v);

public slots:
    void refresh_graph();

private:
    bip::managed_shared_memory segment1, segment2;
    double *freq1, *freq2;
    QProcess process1, process2;

    QVector<QPointF> points;
    QLineSeries main_series;
    QChart chart;
};

} // wiet_star

#endif // DIFFERENCE_GRAPH_HPP
