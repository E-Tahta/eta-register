#include "additionaldatacollector.h"
#include "detectiwb.h"
#include <QDebug>
#include <QString>
#include <cpuid.h>
#include <iostream>
#include <map>
#include <string>


AdditionalDataCollector::AdditionalDataCollector(QObject *parent) :
    QObject(parent),
    m_touch("0"),
    m_cpu("0")
{
    diwb = new DetectIWB(this);
}

void AdditionalDataCollector::collectAdditionalInfos()
{
    getCpuInfo();
    getTouchInfo();
}

void AdditionalDataCollector::getCpuInfo()
{
    unsigned int level = 0;
    unsigned int eax = 0;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;

    __get_cpuid(level, &eax, &ebx, &ecx, &edx);

    CPUVendorID vendorID { .ebx = ebx, .edx = edx, .ecx = ecx };

    map<string, string> vendorIdToName;
    vendorIdToName["GenuineIntel"] = "Intel";
    vendorIdToName["AuthenticAMD"] = "AMD";
    vendorIdToName["CyrixInstead"] = "Cyrix";
    vendorIdToName["CentaurHauls"] = "Centaur";
    vendorIdToName["SiS SiS SiS "] = "SiS";
    vendorIdToName["NexGenDriven"] = "NexGen";
    vendorIdToName["GenuineTMx86"] = "Transmeta";
    vendorIdToName["RiseRiseRise"] = "Rise";
    vendorIdToName["UMC UMC UMC "] = "UMC";
    vendorIdToName["Geode by NSC"] = "National Semiconductor";

    string vendorIDString = vendorID.toString();

    auto it = vendorIdToName.find(vendorIDString);

    if (it != vendorIdToName.end()) {
        m_cpu = QString::fromStdString(it->second);
    }
}

void AdditionalDataCollector::getTouchInfo()
{
    m_touch = diwb->getIWBType();
}

QString AdditionalDataCollector::getTouch() const
{
    return m_touch;
}

QString AdditionalDataCollector::getCpu() const
{
    return m_cpu;
}

