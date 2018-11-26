#ifndef DETECTIWB_H
#define DETECTIWB_H

#include <QObject>
#include <QString>

class DetectIWB : public QObject
{
    Q_OBJECT
public:
    explicit DetectIWB(QObject *parent = 0);
    bool isIWB() const;
    QString getIWBType() const;
private:    
    bool m_found;
    QString m_iwbTouchInfo;

};

#endif // DETECTIWB_H
