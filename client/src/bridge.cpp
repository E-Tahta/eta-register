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

#include "bridge.h"
#include "networkmanager.h"
#include "requestmanager.h"
#include <QDBusConnection>
#include <QDBusInterface>

Bridge::Bridge(QObject *parent) :
    QObject(parent)
{
    resultStr = "unkown";
    nm = new NetworkManager(this);
    rm = new RequestManager(this);

    connect(rm,SIGNAL(gotResult(QString,bool)),
            this,SLOT(gotResult(QString,bool)));

    QDBusConnection dbus = QDBusConnection::sessionBus();
    qdi = new QDBusInterface("org.eta.virtualkeyboard",
                                   "/VirtualKeyboard",
                                   "org.eta.virtualkeyboard",
                                   dbus,
                                   this);

}

Bridge::~Bridge(){

}

void Bridge::sendData(const QString& city, const QString& town,
                      const QString& school, const QString& code) {

    rm->insertData(nm->getMac(), city, town, school, code);

}

QString Bridge::result() const
{
    return resultStr;
}

void Bridge::gotResult(QString s, bool b)
{
    QString out = "";
    if(s == "0") {        
        out = "Request EXISTS is ";
        out += b ? "TRUE" : "FALSE";
        if(b) {
            emit close();
        } else {
            emit showGui();
        }
    } else if(s == "1") {
        out = "Request INSERT is ";
        out += b ? "SUCCESSFUL" : "UNSUCCESSFUL";
    } else {
        out = "Request "+s+" is "+b;
    }
    resultStr = out;
    emit resultRecieved();
}

void Bridge::isOnline()
{
    if ( nm-> isOnline() ) {
        rm->doesMacIdExist(nm->getMac());
    } else {
     //   emit close();
    }
}

void Bridge::showKeyboard()
{
    qdi->call("showFromBottom");
}

void Bridge::hideKeyboard()
{
    qdi->call("hide");
}