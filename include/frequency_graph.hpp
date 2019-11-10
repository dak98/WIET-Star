#ifndef WIET_STAR_FREQUENCY_GRAPH_HPP
#define WIET_STAR_FREQUENCY_GRAPH_HPP

#include <QtCharts/QChartView>

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
QT_CHARTS_USE_NAMESPACE

#include <QtCore/QTimer>

#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>

#include <memory>

namespace wiet_star
{

struct freq_graph_config
{
    qreal min_frequency;
    qreal max_frequency;

    qreal min_amplitude;
    qreal max_amplitude;
};

struct input_audio_config
{
    QString device_name;
    int channel_count;

    int sample_rate;
    int sample_size;
    QAudioFormat::SampleType sample_type;

    QString codec;
    QAudioFormat::Endian byte_order;

    int buffer_size;
};

class frequency_graph : public QChartView
{
    Q_OBJECT
public:
    frequency_graph(freq_graph_config const& graph_config,
                    input_audio_config const& audio_config);

    ~frequency_graph();

private slots:
    void refresh_graph();

private:
    unsigned sample_rate;
    unsigned sample_size;

    QChart main_graph;
    QLineSeries main_series;
    QValueAxis x_axis, y_axis;

    QAudioDeviceInfo input_device;
    QAudioFormat input_audio_format;
    std::unique_ptr<QAudioInput> input_handle;

    std::unique_ptr<QIODevice> input_buffer;

    std::unique_ptr<QTimer> refresh_timer;
};

} // wiet_star

#endif // WIET_STAR_FREQUENCY_GRAPH_HPP
