#ifndef AUDIO_INPUT_RECORDER_HPP
#define AUDIO_INPUT_RECORDER_HPP

#include <QChartView>

#include <QtMultimedia/QAudioInput>

#include <harmonics_iodevice.hpp>

QT_CHARTS_USE_NAMESPACE

namespace wiet_star
{

enum recorder_type
{
    MICROPHONE,
    CAPTURE
};

class audio_input_recorder : public QChartView
{
    Q_OBJECT
public:
    explicit audio_input_recorder(recorder_type type, QWidget *parent = nullptr);
    ~audio_input_recorder();

    std::optional<double> get_last_harmonic() const { return last_harmonic; }

public slots:
    void set_last_harmonic(double const h) { last_harmonic = h; }

private:
    harmonics_iodevice* io_device;
    QAudioInput* input_device;

    std::optional<double> last_harmonic;
};

} // wiet_star    

#endif // AUDIO_INPUT_RECORDER_HPP
