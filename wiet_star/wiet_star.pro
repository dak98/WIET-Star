QT += multimedia widgets charts quick

QMAKE_CXXFLAGS += -std=c++17
LIBS += -lrt -lpthread

HEADERS += include/wiet_star_window.hpp \
           include/difference_graph.hpp \
    include/directory_listing.hpp \
    include/audio_player.hpp

SOURCES += src/main.cpp \
           src/wiet_star_window.cpp \
           src/difference_graph.cpp \
    src/directory_listing.cpp \
    src/audio_player.cpp

FORMS +=

INCLUDEPATH += include

RESOURCES += qml.qrc
