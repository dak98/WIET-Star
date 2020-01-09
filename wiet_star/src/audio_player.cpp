#include <audio_player.hpp>

namespace wiet_star
{

audio_player::audio_player(QObject *parent)
    : QObject{parent} {}

audio_player::~audio_player()
{
    if (player != nullptr)
        delete player;
}

void audio_player::play(QUrl const& path)
{
    if (player != nullptr)
    {
        qDebug() << "Song is playing or error has occured";
        return;
    }

    player = new QMediaPlayer;

    player->setMedia(path);
    player->setVolume(50);
    player->play();

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &audio_player::stop);
}

void audio_player::stop()
{
    if (player == nullptr)
    {
        qDebug() << "No song is being played";
        return;
    }

    if (player->mediaStatus() == QMediaPlayer::EndOfMedia) // Song ended normally
    {
        emit song_ended();

        delete player;
    }
}

void audio_player::set_volume(int const volume)
{
    if (player == nullptr)
    {
        qDebug() << "No song is being played";
        return;
    }
    player->setVolume(volume);
}

} // wiet_star
