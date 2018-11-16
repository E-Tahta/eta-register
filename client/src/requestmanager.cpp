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

#include "requestmanager.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QDebug>


RequestManager::RequestManager(QObject *parent) :
    QObject(parent)
{
    nam = new QNetworkAccessManager(this);
    request = new QNetworkRequest(QUrl(URL));
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    connect(nam, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(requestFinished(QNetworkReply*)));
}


void RequestManager::doesMacIdExist(const QString &mac_id,
                                    const QString &touch,
                                    const QString &cpu)
{
    QJsonObject data;
    data.insert("mac_id", mac_id);
    data.insert("city", "");
    data.insert("town", "");
    data.insert("school", "");
    data.insert("code", "");
    data.insert("cpu", cpu);
    data.insert("touch", touch);
    data.insert("request_type",EXISTS);
    data.insert("result","");
    nam->post(*request, QJsonDocument(data).toJson());
}

void RequestManager::insertData(const QString& mac_id,const QString& city,
                                const QString& town, const QString& school,
                                const QString& code, const QString &cpu,
                                const QString &touch)
{
    QJsonObject data;
    data.insert("mac_id", mac_id);
    data.insert("city", city);
    data.insert("town", town);
    data.insert("school", school);
    data.insert("code", code);
    data.insert("cpu", cpu);
    data.insert("touch", touch);
    data.insert("request_type",INSERT);
    data.insert("result","");

    nam->post(*request, QJsonDocument(data).toJson());
}

void RequestManager::requestFinished(QNetworkReply *r)
{
    QByteArray response_data = r->readAll();
    QJsonDocument response_doc = QJsonDocument::fromJson(response_data);
    QJsonObject response = response_doc.object();
    bool b = response.value("result").toBool();
    QString s = response.value("request_type").toString();

    emit gotResult(s,b);
}
