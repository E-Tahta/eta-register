TEMPLATE = app

QT += qml quick widgets network

SOURCES += main.cpp \
    bridge.cpp \
    requestmanager.cpp \
    networkmanager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    bridge.h \
    requestmanager.h \
    networkmanager.h
