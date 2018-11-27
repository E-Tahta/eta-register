/*****************************************************************************
 *   Copyright (C) 2016 by Yunusemre Senturk                                 *
 *   <yunusemre.senturk@pardus.org.tr>                                       *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#include "src/bridge.h"
#include "src/singleinstance.h"
#include "src/detectiwb.h"

#include <signal.h>
#include <unistd.h>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QIcon>
#include <QCursor>


#define ICONPATH "/usr/share/eta/eta-register/icon/register.svg"
#define SINGLE_INSTANCE ".eta-register"

static int setup_unix_signal_handlers();

int main(int argc, char *argv[])
{
    DetectIWB iwb;

    if (!iwb.isIWB()) {
        qDebug() << "Could not detect IWB aborting";
        return 1;
    }

    QString uname = qgetenv("USER");
    if (uname.isEmpty())
        uname = qgetenv("USERNAME");

    if (uname.compare("ogrenci") == 0) {
        qDebug() << "Ogrenci is not allowed to use eta-register";
        return 0;
    }

    qmlRegisterType<Bridge>("eta.bridge",1,0,"Bridge");
    QApplication::setWindowIcon( QIcon(ICONPATH) );
    QApplication app(argc, argv);
    app.setOverrideCursor(QCursor(Qt::BlankCursor));

    QString pidName = SINGLE_INSTANCE;
    QString username = qgetenv("USER");
    if (username.isEmpty())
        username = qgetenv("USERNAME");
    QString tmpPath= "/tmp/";
    QString pidPath = tmpPath.append(username);

    QDir dir(pidPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString name = pidPath.append("/").append(pidName);

    SingleInstance cInstance;

    if(cInstance.hasPrevious(name, QCoreApplication::arguments()))
    {
        return 0;
        qDebug("eta-register is allready running");
    }

    if (cInstance.listen(name)) {
        qDebug() << "Creating single instance";
        setup_unix_signal_handlers();
    } else {
        qFatal("Couldn't create single instance aborting");
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));

    return app.exec();
}

static void handle_signal(int sig)
{
    QString pidName = SINGLE_INSTANCE;
    QString username = qgetenv("USER");
    if (username.isEmpty())
        username = qgetenv("USERNAME");
    QString tmpPath= "/tmp/";
    QString pidPath = tmpPath.append(username);
    QString name = pidPath.append("/").append(pidName);
    QByteArray ba = name.toLatin1();
    Q_UNUSED(sig);
    unlink(ba.data());
    exit(0);
}

static int setup_unix_signal_handlers()
{
    struct sigaction sig;
    sig.sa_handler = handle_signal;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_flags |= SA_RESTART;
    if (sigaction(SIGINT, &sig, 0)) {
        return 1;
    }
    if (sigaction(SIGTERM, &sig, 0)) {
        return 2;
    }
    return 0;
}
