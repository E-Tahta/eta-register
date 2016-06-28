#include "bridge.h"
#include "networkmanager.h"
#include "requestmanager.h"
#include <QDebug>

Bridge::Bridge(QObject *parent) :
    QObject(parent)
{
    resultStr = "unkown";
    nm = new NetworkManager(this);
    rm = new RequestManager(this);

    connect(rm,SIGNAL(gotResult(QString,bool)),
            this,SLOT(gotResult(QString,bool)));

}

Bridge::~Bridge(){

}

void Bridge::sendData(const QString& city,
                      const QString& town, const QString& school,
                      const QString& code){

    rm->insertData(nm->getMac(), city, town, school, code);

}

QString Bridge::result() const
{
    return resultStr;
}

void Bridge::gotResult(QString s, bool b)
{
    QString out = "";
    if(s == "0") {        
        out = "Request EXISTS is ";
        out += b ? "TRUE" : "FALSE";
        if(b) {
            emit close();
        } else {
            emit showGui();
        }
    } else if(s == "1") {
        out = "Request INSERT is ";
        out += b ? "SUCCESFULL" : "UNSECCESFULL";
    } else {
        out = "Request "+s+" is "+b;
    }
    resultStr = out;
    emit resultRecieved();
}

void Bridge::isOnline()
{
    if ( nm-> isOnline() ) {
        rm->doesMacIdExist(nm->getMac());
    } else {
        emit close();
    }
}
