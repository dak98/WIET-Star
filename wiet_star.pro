QT += multimedia multimediawidgets widgets charts

QMAKE_CXXFLAGS += -std=c++17
#LIBS += -lrt -lpthread

HEADERS += include/wiet_star_window.hpp \
           include/graphs_stacked_layout.hpp \
           include/directory_listing.hpp \
           include/audio_player.hpp \
           include/audio_input_recorder.hpp \
           include/fft.hpp \
           include/harmonics_iodevice.hpp \
           include/num_range.hpp

SOURCES += src/main.cpp \
           src/wiet_star_window.cpp \
           src/graphs_stacked_layout.cpp \
           src/directory_listing.cpp \
           src/audio_player.cpp \
           src/audio_input_recorder.cpp \
           src/fft.cpp \
           src/harmonics_iodevice.cpp

INCLUDEPATH += include

