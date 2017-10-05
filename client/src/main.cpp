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

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QIcon>
#include <QCursor>
#include "bridge.h"
#include "singleinstance.h"
#define ICONPATH "/usr/share/eta/eta-register/register.svg"
#define SINGLE_INSTANCE ".eta-register"

int main(int argc, char *argv[])
{
    qmlRegisterType<Bridge>("eta.bridge",1,0,"Bridge");
    QApplication::setWindowIcon( QIcon(ICONPATH) );
    QApplication app(argc, argv);
    app.setOverrideCursor(QCursor(Qt::BlankCursor));

    QString name = SINGLE_INSTANCE;
    SingleInstance cInstance;
    if(cInstance.hasPrevious(name, QCoreApplication::arguments()))
    {
        qDebug() << "eta-register is allready open";
        return 0;
    }
    if (cInstance.listen(name)) {
        qDebug() << "creating single instance";
    } else {
        qDebug() << "couldnt create single instance aborting";
        return 0;
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));

    return app.exec();
}
