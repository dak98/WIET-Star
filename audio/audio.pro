QT += multimedia widgets

CONFIG(debug, debug|release) {
    QT += charts
}

QMAKE_CXXFLAGS += -std=c++17
LIBS += -lrt -lpthread  

INCLUDEPATH += include

HEADERS += include/fft.hpp \
           include/num_range.hpp \
           include/audio_input_wrapper.hpp \
           include/harmonics_iodevice.hpp

SOURCES += src/main.cpp \
           src/fft.cpp \
           src/audio_input_wrapper.cpp \
           src/harmonics_iodevice.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/audio
INSTALLS += target
