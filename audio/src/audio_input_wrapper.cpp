#include <audio_input_wrapper.hpp>

#ifdef QT_DEBUG
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QVBoxLayout>
#endif

AudioInputWrapper::AudioInputWrapper(QAudioInput& input_device, double& dest, QWidget *parent)
    : QWidget(parent)
      , input_device(input_device)
#ifdef QT_DEBUG
      , io_device(&series, dest, this)
#else
      , io_device(dest, this)
#endif
{
#ifdef QT_DEBUG
    QChartView* chartView = new QChartView{&chart, this};
    chartView->setMinimumSize(800, 600);
    chart.addSeries(&series);
    QValueAxis *axisX = new QValueAxis{this};
    axisX->setRange(0, 100);
    QValueAxis *axisY = new QValueAxis{this};
    axisY->setRange(250, 4000);
    axisY->setTitleText("Frequency level");
    axisX->setMinorTickCount(2);
    chart.setAxisX(axisX, &series);
    chart.setAxisY(axisY, &series);
    chart.legend()->hide();

    QVBoxLayout *mainLayout = new QVBoxLayout{this};
    mainLayout->addWidget(chartView);
#endif

    io_device.open(QIODevice::WriteOnly);
    input_device.start(&io_device);
}

AudioInputWrapper::~AudioInputWrapper()
{
    input_device.stop();
    io_device.close();
}
