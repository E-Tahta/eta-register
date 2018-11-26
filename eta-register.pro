TEMPLATE = app

QT += qml quick widgets network dbus sql
CONFIG += c++11
SOURCES += src/main.cpp \
    src/bridge.cpp \
    src/requestmanager.cpp \
    src/networkmanager.cpp \
    src/singleinstance.cpp \
    src/detectiwb.cpp \
    src/databasemanager.cpp \
    src/additionaldatacollector.cpp \
    src/watchdistro.cpp \
    src/fileio.cpp

RESOURCES += qml.qrc images.qrc

QML_IMPORT_PATH =

HEADERS += \
    src/bridge.h \
    src/requestmanager.h \
    src/networkmanager.h \
    src/singleinstance.h \
    src/detectiwb.h \
    src/databasemanager.h \
    src/additionaldatacollector.h \
    src/watchdistro.h \
    src/fileio.h

TARGET = eta-register

target.path = /usr/bin/

icon.files = register.svg
icon.commands = mkdir -p /usr/share/eta/eta-register/icon
icon.path = /usr/share/eta/eta-register/icon/

desktop_file.files = eta-register.desktop
desktop_file.path = /usr/share/applications/

database_file.files = register.db
database_file.commands = mkdir -p /usr/share/eta/eta-register
database_file.path = /usr/share/eta/eta-register/

auto_start.files = eta-register-autostart.desktop
auto_start.commands = mkdir -p /etc/xdg/autostart
auto_start.path = /etc/xdg/autostart/

INSTALLS += target icon desktop_file database_file auto_start

LIBS += -lcurl

