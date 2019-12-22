#include <wiet_star_window.hpp>

#include <QTimer>

namespace wiet_star
{

wiet_star_window::wiet_star_window(QWidget *parent)
    : QMainWindow{parent}
      , segment1{bip::open_or_create, "Audio1", 65536}
      , segment2{bip::open_or_create, "Audio2", 65536}
{
    freq1 = segment1.find_or_construct<double>("double")();
    freq2 = segment2.find_or_construct<double>("double")();

    points.reserve(100);
    for (int i = 0; i < 100; i++)
        points.push_back(QPointF{static_cast<qreal>(i), 0});

    setWindowTitle("WIET STAR");

    QChartView* chart_view = new QChartView{&chart, this};
    QValueAxis* axisX = new QValueAxis{this};
    QValueAxis* axisY = new QValueAxis{this};
    chart_view->setMinimumSize(800, 600);
    chart.addSeries(&main_series);
    axisX->setRange(0, 100);
    axisY->setRange(-4000, 4000);
    axisX->setMinorTickCount(2);
    chart.setAxisX(axisX, &main_series);
    chart.setAxisY(axisY, &main_series);
    chart.legend()->hide();

    main_series.replace(points);
    setCentralWidget(chart_view);

#ifdef QT_DEBUG
    process1.start("../build-audio-Desktop-Debug/audio", {"Audio1"});
    process2.start("../build-audio-Desktop-Debug/audio", {"Audio2"});
#else
    process1.start("../build-audio-Desktop-Release/audio", {"Audio1"});
    process2.start("../build-audio-Desktop-Release/audio", {"Audio2"});
#endif

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &wiet_star_window::refresh_graph);
    timer->start(35);
}

wiet_star_window::~wiet_star_window()
{
    process1.kill();
    process2.kill();

    bip::shared_memory_object::remove("Audio1");
    bip::shared_memory_object::remove("Audio2");
}

void wiet_star_window::refresh_graph()
{
    // For C++20, std::shift_left could be used.
    for (int i = 0; i < 99; i++)
    {
        points[i].setY(points[i + 1].y());
        points[99].setY(*freq1 - *freq2);
    }

    main_series.replace(points);
}

} // wiet_star
