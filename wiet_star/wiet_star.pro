QT += multimedia widgets charts quick

QMAKE_CXXFLAGS += -std=c++17
LIBS += -lrt -lpthread

HEADERS += include/wiet_star_window.hpp

SOURCES += src/main.cpp \
           src/wiet_star_window.cpp \

INCLUDEPATH += include

DISTFILES +=

RESOURCES += \
    qml.qrc
