/*
  Copyright 2020 Jakub Czajka

  This file is part of WietStar.

  WietStar is free software: you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or (at your option) any later
  version.

  WietStar is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  WietStar. If not, see <https://www.gnu.org/licenses/>.
*/

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
