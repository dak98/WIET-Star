#include <audio_input_recorder.hpp>

#include <QAudioDeviceInfo>
#include <QLineSeries>
#include <QValueAxis>

#include <QDebug>

namespace wiet_star
{

audio_input_recorder::audio_input_recorder(recorder_type type, QWidget *parent)
    : QChartView {parent}
{
    QValueAxis* axis_x = new QValueAxis;
    axis_x->setRange(0, 100);
    axis_x->setMinorTickCount(2);

    QValueAxis* axis_y = new QValueAxis;
    axis_y->setRange(250, 4000);
    axis_y->setTitleText("Frequency level");

    QLineSeries* series = new QLineSeries;

    QChart* chart = new QChart;
    chart->addSeries(series);
    chart->setAxisX(axis_x, series);
    chart->setAxisY(axis_y, series);
    chart->legend()->hide();

    setChart(chart);

    QList<QAudioDeviceInfo> devices {QAudioDeviceInfo::availableDevices(QAudio::AudioInput)};
    QAudioDeviceInfo const info {(type == recorder_type::CAPTURE) ? devices[0] : devices[8]};
    
    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    io_device = new harmonics_iodevice {series};
    io_device->open(QIODevice::WriteOnly);

    connect(io_device, &harmonics_iodevice::new_harmonic, this, &audio_input_recorder::set_last_harmonic);

    input_device = new QAudioInput {info, format};
    input_device->start(io_device);
}

audio_input_recorder::~audio_input_recorder()
{
    input_device->stop();
    io_device->close();

    delete io_device;
    delete input_device;
}

} // wiet_star
