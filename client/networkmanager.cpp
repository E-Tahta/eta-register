#include "networkmanager.h"
#include <QList>
#include <QNetworkInterface>

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent)
{
    Mac = "unknown";
    setMac();

}

bool NetworkManager::isOnline()
{

    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    bool result = false;

    for (int i = 0; i < ifaces.count(); i++) {

        QNetworkInterface iface = ifaces.at(i);
        if ( iface.flags().testFlag(QNetworkInterface::IsUp)
             && !iface.flags().testFlag(QNetworkInterface::IsLoopBack)) {

            for (int j=0; j<iface.addressEntries().count(); j++) {
                if (result == false)
                    result = true;
            }
        }

    }

    return result;
}

void NetworkManager::setMac()
{
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();

    for (int i = 0; i < ifaces.count(); i++) {
        QNetworkInterface iface = ifaces.at(i);
        if ( !iface.flags().testFlag(QNetworkInterface::IsLoopBack)
             && iface.name().contains("eth")) {
            Mac = QString(iface.hardwareAddress().toUtf8());
        }

    }
}

QString NetworkManager::getMac() const
{
    return Mac;
}
