#include "detectiwb.h"
#include "fileio.h"

DetectIWB::DetectIWB(QObject *parent) : QObject(parent),
  m_found(false), m_iwbTouchInfo("Unknown optic touch device")
{
    FileIO f;
    QString info = f.readIWBInfo();

    if(!info.isNull()) {
        m_found = true;
        if(info.toUInt() == 2) {
            m_iwbTouchInfo = "4 point optic touch";
        } else if (info.toUInt() == 1) {
            m_iwbTouchInfo = "2 point optic touch";
        } else {
            m_found = false;
        }
    } else {
        m_found = false;
    }
}

bool DetectIWB::isIWB() const
{
    return m_found;
}

QString DetectIWB::getIWBType() const
{
    return m_iwbTouchInfo;
}

