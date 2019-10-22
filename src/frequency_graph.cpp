#include <frequency_graph.hpp>

#include <QtCore/QDebug>

#include <system_error>
#include <thread>
#include <unistd.h>

#include <iostream>

namespace wiet_star
{

frequency_graph::frequency_graph(freq_graph_config const& graph_config,
                                 input_audio_config const& audio_config)
    : refresh_timer(new QTimer(this))
{
    x_axis.setTitleText("Częstotliwość");
    x_axis.setRange(graph_config.min_frequency, graph_config.max_frequency);

    y_axis.setTitleText("Amplituda");
    y_axis.setRange(graph_config.min_amplitude, graph_config.max_amplitude);

    main_graph.addSeries(&main_series);
    main_graph.legend()->hide();
    main_graph.setAxisX(&x_axis, &main_series);
    main_graph.setAxisY(&y_axis, &main_series);
    main_graph.setTitle("Wynik transformaty Fouriera");

    setChart(&main_graph);

    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    bool device_not_found = true;
    for (auto it = std::begin(devices); it != std::end(devices) && device_not_found; ++it)
        if (it->deviceName() == audio_config.device_name)
        {
            input_device = *it;
            device_not_found = false;
        }

    if (input_device.isNull())
    {
        input_device = QAudioDeviceInfo::defaultInputDevice();
        qDebug() << "Device " + audio_config.device_name + " not found. Using " +
                    "the default one";
    }

    input_audio_format.setChannelCount(audio_config.channel_count);
    input_audio_format.setSampleRate(audio_config.sample_rate);
    input_audio_format.setSampleSize(audio_config.sample_size);
    input_audio_format.setSampleType(audio_config.sample_type);
    input_audio_format.setCodec(audio_config.codec);
    input_audio_format.setByteOrder(audio_config.byte_order);

    if (!input_device.isFormatSupported(input_audio_format))
    {
        qWarning() << "Default format not supported, trying to use the nearest.";
        input_audio_format = input_device.nearestFormat(input_audio_format);
    }

    input_handle = std::unique_ptr<QAudioInput>(new QAudioInput(input_device, input_audio_format));
    if (input_handle->error() != QAudio::NoError)
    {
        qDebug() << "QAudioInput error: " << input_handle->error();
        throw std::system_error(std::make_error_code(std::errc::io_error));
    }

    input_buffer = std::unique_ptr<QIODevice>(input_handle->start());
    if (input_handle->error() != QAudio::NoError)
    {
        qDebug() << "QAudioInput#start error: " << input_handle->error();
        throw std::system_error(std::make_error_code(std::errc::io_error));
    }

    connect(refresh_timer.get(), &QTimer::timeout, this, &frequency_graph::refresh_graph);
    refresh_timer->start(5000);
}

frequency_graph::~frequency_graph()
{
    refresh_timer->stop();
    input_handle->stop();
    input_buffer->close();
}

void frequency_graph::refresh_graph()
{
    char audio_data[100];
    if (-1 == input_buffer->read(audio_data, 100))
    {
        std::cout << audio_data << std::endl;
    }

    qreal step = (x_axis.max() - x_axis.min()) / 100;
    QVector<QPointF> points(100);
    for (int i = 0; i < 100; i++)
    {
        points[i].setX(x_axis.min() + i * step);
        qreal y = uchar(audio_data[i]);
        points[i].setY(y / 128);
    }
    main_series.replace(points);
}

} // wiet_star
