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

#ifndef WIET_STAR_WINDOW_HPP
#define WIET_STAR_WINDOW_HPP

#include <QWidget>

#include <QLabel>
#include <QMediaPlayer>

#include <audio_player.hpp>
#include <directory_listing.hpp>

namespace wiet_star
{

class wiet_star_window : public QWidget
{
    Q_OBJECT

public:
    wiet_star_window(QString const& playlist_dir, QWidget *parent = nullptr);

public slots:
    void set_menu_layout();
    void set_game_layout();
    void update_score(double const new_value);
    void write_result();

private:
    QString const playlist_dir;
    std::optional<QString> last_song;
    directory_listing* playlist;

    double score {0.0};
    QLabel* score_label;
};

} // wiet_star

#endif // WIET_STAR_WINDOW_HPP
