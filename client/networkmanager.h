#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>


class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = 0);

private:
    QString Mac;
    void setMac();

public slots:
    bool isOnline();
    QString getMac() const;

};

#endif // NETWORKMANAGER_H
