#include "wiet_star_window.hpp"

namespace wiet_star
{

wiet_star_window::wiet_star_window(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(&transform_result);
}

} // wiet_star
