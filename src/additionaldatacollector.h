#ifndef ADDITIONALDATACOLLECTOR_H
#define ADDITIONALDATACOLLECTOR_H

#include <QObject>
class DetectIWB;

using namespace std;

class AdditionalDataCollector : public QObject
{
    Q_OBJECT
public:
    explicit AdditionalDataCollector(QObject *parent = 0);

    void collectAdditionalInfos();
    void getCpuInfo();
    void getTouchInfo();

    QString m_touch;
    QString m_cpu;

    QString getTouch() const;
    QString getCpu() const;

private:
    DetectIWB *diwb;
    struct CPUVendorID {
        unsigned int ebx;
        unsigned int edx;
        unsigned int ecx;

        string toString() const {
            return string(reinterpret_cast<const char *>(this), 12);
        }
    };

signals:

};

#endif // ADDITIONALDATACOLLECTOR_H
