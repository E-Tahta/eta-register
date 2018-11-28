#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QSqlDatabase>

class Logger;

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();


    void getInfo(const QString &code);

private:
    QString m_code;
    QString m_city;
    QString m_cityID;
    QString m_town;
    QString m_school;
    QSqlDatabase db;

    Logger *logger;

    void DatabaseConnect();
    bool getCity(QString &cityName);

signals:
    void infoCollected(const QStringList &datas);
    void dbError(const int &errorType);
};

#endif // DATABASEMANAGER_H
