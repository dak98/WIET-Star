#ifndef WIET_STAR_WINDOW_HPP
#define WIET_STAR_WINDOW_HPP

#include <QMainWindow>

#include <frequency_graph.hpp>

namespace wiet_star
{

class wiet_star_window : public QMainWindow
{
    Q_OBJECT
public:
    wiet_star_window(freq_graph_config const& graph_config,
                     input_audio_config const& audio_config,
                     QWidget *parent = nullptr);

signals:

public slots:

private:
    frequency_graph transform_result;
};

} // wiet_star

#endif // WIET_STAR_WINDOW_HPP
