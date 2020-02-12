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

#include <wiet_star_window.hpp>

#include <QCheckBox>
#include <QComboBox>
#include <QDate>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVideoWidget>

#include <graphs_stacked_layout.hpp>

namespace wiet_star
{

wiet_star_window::wiet_star_window(QString const& playlist_dir, QWidget *parent)
    : QWidget{parent},
      playlist_dir{playlist_dir}
{
    resize(800, 600);
    set_menu_layout();
}

void wiet_star_window::set_menu_layout()
{
    playlist = new directory_listing{playlist_dir, "*.mp4"};
    QListWidget* leaderboard = new QListWidget;

    QFile results_file {"RESULTS.txt"};
    if (results_file.open(QIODevice::ReadOnly))
    {
        QTextStream strm {&results_file};
        while (!strm.atEnd())
            leaderboard->addItem(strm.readLine());

        results_file.close();
    }

    QPushButton* exit_button= new QPushButton{"EXIT"};
    QPushButton* refresh_button = new QPushButton{"REFRESH"};
    QPushButton* play_button = new QPushButton{"PLAY"};

    connect(exit_button, &QPushButton::clicked, this, &QWidget::close);
    connect(refresh_button, &QPushButton::clicked, playlist, &directory_listing::refresh);
    connect(play_button, &QPushButton::clicked, this, &wiet_star_window::set_game_layout);

    QHBoxLayout* buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(exit_button);
    buttons_layout->addWidget(refresh_button);
    buttons_layout->addWidget(play_button);

    QHBoxLayout* lists_layout = new QHBoxLayout;
    lists_layout->addWidget(playlist);
    lists_layout->addWidget(leaderboard);

    QVBoxLayout* buttons_playlist_layout = new QVBoxLayout;
    buttons_playlist_layout->addLayout(lists_layout);
    buttons_playlist_layout->addLayout(buttons_layout);

    qDeleteAll(children());
    setLayout(buttons_playlist_layout);
}

void wiet_star_window::set_game_layout()
{
    if (!playlist->is_item_highlighted())
        return;

    QPushButton* exit_button = new QPushButton {"STOP AND EXIT"};
    connect(exit_button, &QPushButton::clicked, this, &wiet_star_window::set_menu_layout);
    QSlider* volume_slider = new QSlider {Qt::Horizontal};
    volume_slider->setMaximum(100);
    volume_slider->setValue(50);
    score_label = new QLabel {"Score: 0.0"};

    QHBoxLayout* bottom_panel_layout = new QHBoxLayout;
    bottom_panel_layout->addWidget(exit_button);
    bottom_panel_layout->addWidget(volume_slider);
    bottom_panel_layout->addWidget(score_label);

    graphs_stacked_layout* graphs = new graphs_stacked_layout;
    connect(graphs, &graphs_stacked_layout::last_diff_value, this, &wiet_star_window::update_score);

    audio_player* player = new audio_player {exit_button};
    connect(volume_slider, &QSlider::valueChanged, player, &audio_player::set_volume);
    connect(player, &audio_player::song_ended, [this]()
    {
        write_result();
        set_menu_layout();
    });

    QVideoWidget* video_display = new QVideoWidget;
    player->set_video_widget(video_display);
    video_display->hide();

    QHBoxLayout* video_graph_layout = new QHBoxLayout;
    video_graph_layout->addWidget(video_display);
    video_graph_layout->addLayout(graphs);

    QComboBox* graph_selection = new QComboBox;
    graph_selection->addItem(tr("Difference Graph"));
    graph_selection->addItem(tr("Audio Capture Graph"));
    graph_selection->addItem(tr("Microphone's Audio Graph"));

    connect(graph_selection, SIGNAL(activated(int)), graphs, SLOT(setCurrentIndex(int)));

    QCheckBox* video_display_switch = new QCheckBox {"Video Display [ON/OFF]"};
    connect(video_display_switch, &QCheckBox::stateChanged, [video_display](int state)
    {
        if (state == Qt::CheckState::Checked)
            video_display->show();
        else
            video_display->hide();
    });

    QHBoxLayout* top_panel_layout = new QHBoxLayout;
    top_panel_layout->addWidget(video_display_switch);
    top_panel_layout->addWidget(graph_selection);

    QVBoxLayout* game_layout = new QVBoxLayout;
    game_layout->addLayout(top_panel_layout);
    game_layout->addLayout(video_graph_layout);
    game_layout->addLayout(bottom_panel_layout);

    last_song = playlist->get_current_item();
    QFileInfo const path {playlist_dir + "/" + last_song.value() + ".mp4"};
    QString const abs_path {path.absoluteFilePath()};
    player->play(QUrl::fromLocalFile(abs_path));

    qDeleteAll(children());
    setLayout(game_layout);
}

void wiet_star_window::update_score(double const new_value)
{
    if (new_value > 1)
    {
        score += 1 / new_value * 0.1;
        score_label->setText("Score: " + QString::number(score));
    }
}

void wiet_star_window::write_result()
{
    QFile f {"RESULTS.txt"};
    if (f.open(QIODevice::Append | QIODevice::WriteOnly))
    {
        QTextStream strm {&f};
        strm << "[" << QDate::currentDate().toString() << "] "
             << last_song.value() << " : " << QString::number(score)
             << "\n";

        f.close();
    }
}

} // wiet_star
