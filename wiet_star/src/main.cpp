#include <QtWidgets/QApplication>

#include <wiet_star_window.hpp>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    wiet_star::wiet_star_window main_window;
    main_window.show();

    return app.exec();
}
