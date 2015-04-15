    TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp \
    parallelzombiegameoflife.cpp \
    gameconfig.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    parallelzombiegameoflife.h \
    gameconfig.h

