#include "wiet_star_window.hpp"

namespace wiet_star
{

wiet_star_window::wiet_star_window(freq_graph_config const& graph_config,
                                   input_audio_config const& audio_config,
                                   QWidget *parent)
    : QMainWindow(parent),
      transform_result(graph_config, audio_config)
{
    setWindowTitle("WIET STAR");
    setCentralWidget(&transform_result);
}

} // wiet_star
