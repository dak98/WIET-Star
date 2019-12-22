#include <QtWidgets/QApplication>
#include <audio_input_wrapper.hpp>

#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>
namespace bip = boost::interprocess;
using shm = bip::managed_shared_memory;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Wrong number of parameters" << std::endl;
        exit(EXIT_FAILURE);
    }

    QApplication app(argc, argv);

    auto list = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    QAudioDeviceInfo const audio_device_info = list[0];
    if (audio_device_info.isNull())
    {
        std::cout << "There is no audio input device available" << std::endl;
        exit(EXIT_FAILURE);
    }

    QAudioFormat audio_format;
    audio_format.setSampleRate(48000);
    audio_format.setChannelCount(1);
    audio_format.setSampleSize(8);
    audio_format.setCodec("audio/pcm");
    audio_format.setByteOrder(QAudioFormat::LittleEndian);
    audio_format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioInput input_device(audio_device_info, audio_format);

    shm segment(bip::open_or_create, argv[1], 65536);
    double* dest = segment.find_or_construct<double>("double")();

    AudioInputWrapper w(input_device, *dest);

#ifdef QT_DEBUG
    w.show();
#endif

    return app.exec();
}
