#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QString>

class NetworkManager;
class RequestManager;


class Bridge : public QObject
{
    Q_OBJECT
public:
    explicit Bridge(QObject *parent = 0);
    ~Bridge();

    Q_INVOKABLE void sendData(const QString &city,
                              const QString& town, const QString& school,
                              const QString& code);
    Q_INVOKABLE void isOnline();
    Q_PROPERTY(QString result READ result
               NOTIFY close NOTIFY showGui NOTIFY resultRecieved)
    QString resultStr;
    QString result() const;
private:
    NetworkManager *nm;
    RequestManager *rm;

private slots:
    void gotResult(QString s, bool b);


signals:
    void close();
    void showGui();
    void resultRecieved();
public slots:

};

#endif // BRIDGE_H
