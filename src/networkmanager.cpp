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

#include "networkmanager.h"
#include "logger.h"
#include <QList>
#include <QNetworkInterface>
#include <QtNetwork>

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent),
    mac("")
{
    logger = new Logger(this);
}

bool NetworkManager::isOnline()
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol
                && address != QHostAddress(QHostAddress::LocalHost)) {
            logger->log("IP Address: "
                        + logger->green_color
                        + address.toString()
                        + logger->no_color);

            logger->log( "trying to reach server"
                         + logger->no_color);

            QNetworkAccessManager nam;
            QNetworkRequest req(QUrl("http://193.140.98.145/phpmyadmin"));
            QNetworkReply *reply = nam.get(req);
            QEventLoop loop;
            connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            if (reply->bytesAvailable()) {
                logger->log(logger->green_color
                            + "server available"
                            + logger->no_color);
                return true;
            }
        }
    }
    return false;
}

void NetworkManager::setMac()
{
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();

    for (int i = 0; i < ifaces.count(); i++) {
        QNetworkInterface iface = ifaces.at(i);
        if ( !iface.flags().testFlag(QNetworkInterface::IsLoopBack)
             && iface.name().contains("eth")) {
            mac = QString(iface.hardwareAddress().toUtf8());
        }
    }
}

QString NetworkManager::getMac() const
{
    return mac;
}
