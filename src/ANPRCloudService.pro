TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/include/x86_64-linux-gnu/

LIBS += -L/usr/lib/x86_64-linux-gnu/
LIBS += -lcurl

SOURCES += \
        anprcloudrequest.cpp \
        anprcloudservice.cpp \
        anprcloudserviceexception.cpp \
        binaryimage.cpp \
        main.cpp \
        multipartbuilder.cpp

HEADERS += \
    anprcloudrequest.h \
    anprcloudresult.h \
    anprcloudservice.h \
    anprcloudserviceexception.h \
    binaryimage.h \
    curltools.hpp \
    json.hpp \
    multipartbuilder.h \
    vehicle.h
