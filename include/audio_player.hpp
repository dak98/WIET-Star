#ifndef AUDIO_PLAYER_HPP
#define AUDIO_PLAYER_HPP

#include <QObject>

#include <QMediaPlayer>

namespace wiet_star
{

class audio_player : public QObject
{
    Q_OBJECT

public:
    audio_player(QObject *parent = nullptr);
    ~audio_player();

    void set_video_widget(QVideoWidget* widget) { video_widget = widget; }

signals:
    void song_ended();

public slots:
    void play(QUrl const& path);
    void stop();
    void set_volume(int const volume);

private:
    QMediaPlayer* player {nullptr};
    std::optional<QVideoWidget*> video_widget;
};

} // wiet_star

#endif // AUDIO_PLAYER_HPP
