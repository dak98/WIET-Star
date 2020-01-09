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
    audio_player* player;
    std::optional<QString> last_song;
    directory_listing* playlist;

    double score {0.0};
    QLabel* score_label;
};

} // wiet_star

#endif // WIET_STAR_WINDOW_HPP
