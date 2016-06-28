#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QObject>

class QNetworkReply;
class QNetworkAccessManager;
class QNetworkRequest;

#define EXISTS  "0"
#define INSERT  "1"
#define URL "http://etaregister.etap.org.tr/etaRegister.php"

class RequestManager : public QObject
{
    Q_OBJECT
public:
    explicit RequestManager(QObject *parent = 0);

private:
    QNetworkAccessManager *nam;
    QNetworkRequest *request;

signals:
    void gotResult(QString s, bool b);

public slots:
    void doesMacIdExist(const QString& mac_id);
    void requestFinished(QNetworkReply *r);
    void insertData(const QString &mac_id, const QString &city,
                    const QString& town, const QString& school,
                    const QString& code);

};

#endif // REQUESTMANAGER_H
