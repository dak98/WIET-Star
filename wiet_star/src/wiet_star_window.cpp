#include <wiet_star_window.hpp>

#include <QDate>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include <difference_graph.hpp>

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
    playlist = new directory_listing{playlist_dir, "*.mp3"};
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

    QHBoxLayout* exit_score_layout = new QHBoxLayout;
    exit_score_layout->addWidget(exit_button);
    exit_score_layout->addWidget(volume_slider);
    exit_score_layout->addWidget(score_label);

    difference_graph* graph = new difference_graph;
    connect(graph, &difference_graph::last_diff_value, this, &wiet_star_window::update_score);

    QVBoxLayout* game_layout = new QVBoxLayout;
    game_layout->addWidget(graph);
    game_layout->addLayout(exit_score_layout);

    player = new audio_player {game_layout};
    connect(volume_slider, &QSlider::valueChanged, player, &audio_player::set_volume);
    connect(player, &audio_player::song_ended, [&]()
    {
        qDebug() << "punkt1";
        write_result();
        qDebug() << "punkt2";
        set_menu_layout();
        qDebug() << "punkt3";
    });

    last_song = playlist->get_current_item();
    QFileInfo const path {playlist_dir + "/" + last_song.value() + ".mp3"};
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
