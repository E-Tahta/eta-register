#ifndef WATCHDISTRO_H
#define WATCHDISTRO_H

#include <QObject>

class FileIO;
class Logger;

#define DW_URL "https://distrowatch.com/table.php?distribution=pardus"


class WatchDistro : public QObject
{
    Q_OBJECT
public:
    explicit WatchDistro(QObject *parent = 0);

    void watch();

private:
    bool checkDay();
    void writeConfig();
    bool goUrl();

    FileIO *f;
    Logger *logger;


signals:

public slots:

};

#endif // WATCHDISTRO_H
