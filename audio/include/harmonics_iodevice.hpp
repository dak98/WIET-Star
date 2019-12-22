#ifndef WIET_STAR_FIRST_HARMONIC_IO_DEVICE_HPP
#define WIET_STAR_FIRST_HARMONIC_IO_DEVICE_HPP

#include <QtCore/QIODevice>
#include <QtCore/QPointF>
#include <QtCore/QVector>

#include <fft.hpp>

#ifdef QT_DEBUG

#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
#endif

/*
 * This class operates as follows:
 * 1) Reads data from the device linked to it (e.g. the microphone).
 * 2) Performs a Fourier transform on the data read.
 * 3) Extracts the frequency of the first harmonic.
 * 4) Writes the result to the given destination.
 */
class HarmonicsIODevice : public QIODevice
{
    Q_OBJECT
public:
    /*
     * Reference for dest is used instead of a pointer to prevent nullptr
     * dereferencing.
     */
    explicit HarmonicsIODevice(double& dest, QObject *parent = nullptr);
#ifdef QT_DEBUG
    explicit HarmonicsIODevice(QXYSeries *series, double& dest, QObject *parent = nullptr);
#endif

protected:
    qint64 readData(char *data, qint64 maxSize) override;
    qint64 writeData(const char *data, qint64 maxSize) override;

private:
    using size_type = std::vector<sample_type>::size_type;
    using it_diff_type = std::vector<sample_type>::iterator::difference_type;

    std::vector<sample_type> buffer;
    double& dest;

    size_type sample_count = 4096;
    double min_freq = 200;
    double max_freq = 4000;
#ifdef QT_DEBUG
    QXYSeries *series;
#endif
};

#endif // WIET_STAR_FIRST_HARMONIC_IO_DEVICE_HPP
