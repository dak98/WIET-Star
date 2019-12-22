#ifndef WIET_STAR_WINDOW_HPP
#define WIET_STAR_WINDOW_HPP

#include <QMainWindow>

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

class wiet_star_window : public QMainWindow
{
    Q_OBJECT


public:
    wiet_star_window(QWidget *parent = nullptr);
    ~wiet_star_window();

signals:

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

#endif // WIET_STAR_WINDOW_HPP
