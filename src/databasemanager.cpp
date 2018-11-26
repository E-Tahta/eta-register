#include "databasemanager.h"
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#define DATABASE_PATH "/usr/share/eta/eta-register/register.db"

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent),
    m_code(""),
    m_city(""),
    m_town(""),
    m_school("")
{
    DatabaseConnect();
}

DatabaseManager::~DatabaseManager()
{
    db.close();
    db.removeDatabase("QSQLITE");
}

void DatabaseManager::DatabaseConnect()
{
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER)) {
        db = QSqlDatabase::addDatabase(DRIVER);
        db.setDatabaseName(DATABASE_PATH);
        if(!db.open()) {
            qDebug() << "Database connect error : " << QString(db.lastError().text()).toLatin1().data();
        }
    }
    else {
        qWarning() << "Database driver error " << DRIVER;
    }

}

bool DatabaseManager::getCity(QString &cityName)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM cities WHERE name = ?");
    query.addBindValue(cityName);

    if(!query.exec()) {
    } else {
        if(query.first()) {
            if (m_cityID.compare(query.value(0).toString()) != 0)
                m_cityID = query.value(0).toString();
            return true;
        }
    }

    return false;
}

void DatabaseManager::getInfo(const QString &code)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM db WHERE code = ?");
    query.addBindValue(code);

    // 0 db error
    // 1 no data found
    // 2 city not found

    if(!query.exec()) {
        emit dbError(0);
    } else {

        if(query.first()) {
            if (m_code.compare(query.value(0).toString()) != 0)
                m_code = query.value(0).toString();

            if (m_city.compare(query.value(1).toString()) != 0)
                m_city = query.value(1).toString();

            if (m_town.compare(query.value(2).toString()) != 0)
                m_town = query.value(2).toString();

            if (m_school.compare(query.value(3).toString()) != 0)
                m_school = query.value(3).toString();

            if (getCity(m_city)) {
                emit infoCollected({m_code, m_city, m_cityID, m_town, m_school});
            }  else emit dbError(2);

        } else emit dbError(1);
    }
}
