#include "additionaldatacollector.h"

#include <usb.h>
#include <QDebug>
#include <QString>
#include <cpuid.h>
#include <iostream>
#include <map>
#include <string>


AdditionalDataCollector::AdditionalDataCollector(QObject *parent) :
    QObject(parent),
    touch("0"),
    cpu("0")
{

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
        cpu = QString::fromStdString(it->second);
    }
}

void AdditionalDataCollector::getTouchInfo()
{
    uint16_t vendors[2] = {0x6615,0x2621};
    struct usb_bus *bus;
    struct usb_device *dev;
    usb_init();
    usb_find_busses();
    usb_find_devices();
    for (bus = usb_busses; bus; bus = bus->next) {
        for (dev = bus->devices; dev; dev = dev->next) {
            if (vendors[0] == dev->descriptor.idVendor) {
                touch = "6615";
            } else if (vendors[1] == dev->descriptor.idVendor) {
                touch = "2621";
            }
        }
    }
}

QString AdditionalDataCollector::getTouch()
{
    return touch;
}

QString AdditionalDataCollector::getCpu()
{
    return cpu;
}

