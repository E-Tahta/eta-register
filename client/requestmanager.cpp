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

void RequestManager::doesMacIdExist(const QString &mac_id)
{
    QJsonObject data;
    data.insert("mac_id", mac_id);
    data.insert("request_type",EXISTS);
    data.insert("result","");
    nam->post(*request, QJsonDocument(data).toJson());
}

void RequestManager::insertData(const QString& mac_id,const QString& city,
                                const QString& town, const QString& school,
                                const QString& code)
{
    QJsonObject data;
    data.insert("mac_id", mac_id);
    data.insert("city", city);
    data.insert("town", town);
    data.insert("school", school);
    data.insert("code", code);
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
