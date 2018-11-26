#include "watchdistro.h"
#include "fileio.h"

#include <QDebug>
#include <QStringList>
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <QDate>

WatchDistro::WatchDistro(QObject *parent) : QObject(parent)
{
    f = new FileIO(this);
}

void WatchDistro::watch()
{
    if (!checkDay()) {
        goUrl();
        writeConfig();
    }
}

bool WatchDistro::checkDay()
{
    QDate date = QDate::currentDate();

    QString::number(date.day());
    QString::number(date.month());
    QString::number(date.year());

    QString currentDate = QString::number(date.day())+ "-"
            +QString::number(date.month())+ "-"
            +QString::number(date.year());

    QStringList lastDate = f->readData();

    if (lastDate.length() > 0) {
        int x = QString::compare(lastDate[0], currentDate, Qt::CaseInsensitive);
        if (x == 0) {
            qDebug() << "Distro is already been watched";
            return true;
        }
    }

    qDebug() << "Distro is not watched";

    return false;
}

void WatchDistro::writeConfig()
{
    f->writeData();
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool WatchDistro::goUrl()
{
    CURLcode res;
    CURL *curl;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {

        curl_easy_setopt(curl, CURLOPT_URL, "http://www.distrowatch.com/pardus");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        return res != NULL;
    }

    return false;
}
