#include <QtWidgets/QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <wiet_star_window.hpp>

int main(int argc, char* argv[])
{

//    QApplication app(argc, argv);
//    wiet_star::wiet_star_window main_window;
//    main_window.show();

//    return app.exec();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc://../main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
