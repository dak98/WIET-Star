#ifndef WIET_STAR_WINDOW_HPP
#define WIET_STAR_WINDOW_HPP

#include <QMainWindow>

namespace wiet_star
{

class wiet_star_window : public QMainWindow
{
    Q_OBJECT
public:
    explicit wiet_star_window(QWidget *parent = nullptr);

signals:

public slots:
};

} // wiet_star

#endif // WIET_STAR_WINDOW_HPP
