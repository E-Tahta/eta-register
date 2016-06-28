#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "bridge.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<Bridge>("eta.bridge",1,0,"Bridge");
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Test.qml")));

    return app.exec();
}
