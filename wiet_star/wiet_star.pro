QT += multimedia widgets charts

QMAKE_CXXFLAGS += -std=c++17
LIBS += -lrt -lpthread

HEADERS += include/wiet_star_window.hpp

SOURCES += src/main.cpp \
           src/wiet_star_window.cpp

INCLUDEPATH += include
