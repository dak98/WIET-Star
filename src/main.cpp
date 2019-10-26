#include <QtWidgets/QApplication>

#include <wiet_star_window.hpp>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    wiet_star::freq_graph_config graph_config;
    graph_config.min_frequency = 20000;
    graph_config.max_frequency = 40000;
    graph_config.min_amplitude= -1;
    graph_config.max_amplitude= 10;

    wiet_star::input_audio_config audio_config;
    audio_config.device_name = "default";
    audio_config.channel_count = 1;
    audio_config.sample_rate = 8000;
    audio_config.sample_size = 8;
    audio_config.buffer_size = 2000;
    audio_config.sample_type = QAudioFormat::UnSignedInt;
    audio_config.codec = "audio/pcm";
    audio_config.byte_order = QAudioFormat::LittleEndian;

    wiet_star::wiet_star_window main_window(graph_config, audio_config);
    main_window.show();

    return app.exec();
}
