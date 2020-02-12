/*
  Copyright 2020 Jakub Czajka

  This file is part of WietStar.

  WietStar is free software: you can redistribute it and/or modify it under the
  terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 3 of the License, or (at your option) any
  later version.

  WietStar is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  WietStar. If not, see <https://www.gnu.org/licenses/>.
*/

#include <audio_player.hpp>

namespace wiet_star
{

audio_player::audio_player(QObject *parent)
    : QObject{parent} {}

audio_player::~audio_player()
{
    if (player != nullptr)
        player->deleteLater();
}

void audio_player::play(QUrl const& path)
{
    if (player != nullptr)
    {
        qDebug() << "Song is playing or error has occured";
        return;
    }

    player = new QMediaPlayer;

    if (video_widget)
        player->setVideoOutput(*video_widget);

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
        emit song_ended();
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
