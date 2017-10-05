TEMPLATE = app

QT += qml quick widgets network dbus

SOURCES += src/main.cpp \
    src/bridge.cpp \
    src/requestmanager.cpp \
    src/networkmanager.cpp \
    src/singleinstance.cpp

RESOURCES += qml.qrc images.qrc

QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/bridge.h \
    src/requestmanager.h \
    src/networkmanager.h \
    src/singleinstance.h

TARGET = eta-register

target.path = /usr/bin/

icon.files = register.svg
icon.commands = mkdir -p /usr/share/eta/eta-register/icon
icon.path = /usr/share/eta/eta-register/icon/

desktop_file.files = eta-register.desktop
desktop_file.path = /usr/share/applications/

auto_start.files = eta-register.desktop
auto_start.commands = mkdir -p /etc/xdg/autostart
auto_start.path = /etc/xdg/autostart/

register_wrap.files = eta-register-wrap.sh
register_wrap.path = /usr/bin/

INSTALLS += target icon desktop_file auto_start register_wrap
