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

#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QString>

class NetworkManager;
class RequestManager;
class QDBusInterface;
class DatabaseManager;
class AdditionalDataCollector;
class WatchDistro;

class Bridge : public QObject
{
    Q_OBJECT
public:
    explicit Bridge(QObject *parent = 0);
    ~Bridge();

    Q_INVOKABLE void sendData(const QString &city, const QString &town,
                              const QString &school, const QString &code);
    Q_INVOKABLE void showKeyboard();
    Q_INVOKABLE void hideKeyboard();
    Q_INVOKABLE void getData(const QString &code);

    Q_INVOKABLE void isOnline();
    Q_PROPERTY(QString result READ result
               NOTIFY close NOTIFY showGui NOTIFY resultRecieved)

    QString resultStr;
    QString result() const;
private:
    NetworkManager *nm;
    RequestManager *rm;
    QDBusInterface *qdi;
    DatabaseManager *dbm;
    AdditionalDataCollector *adc;
    WatchDistro *wd;
    QString touch;
    QString cpu;
    QString mac;

private slots:
    void gotResult(QString s, bool b);

signals:
    void close();
    void showGui();
    void resultRecieved();
    void infoCollected(const QStringList &datas);
    void dbError(const int &errorType);

public slots:

};

#endif // BRIDGE_H
