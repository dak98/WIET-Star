#ifndef WIET_STAR_WIDGET_HPP
#define WIET_STAR_WIDGET_HPP

#include <QtWidgets/QWidget>
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>

#include <harmonics_iodevice.hpp>

#ifdef QT_DEBUG
#include <QtCharts/QChartGlobal>
#include <QChart>
#include <QLineSeries>
QT_CHARTS_USE_NAMESPACE
#endif

// A RAII wrapper for QAudioInput and HarmonicsIODevice.
class AudioInputWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit AudioInputWrapper(QAudioInput& deviceInfo, double& dest, QWidget *parent = nullptr);
    ~AudioInputWrapper();

private:
    QAudioInput& input_device;
#ifdef QT_DEBUG
    QChart chart;
    QLineSeries series;
#endif
    HarmonicsIODevice io_device;
};

#endif // WIET_STAR_WIDGET_HPP
