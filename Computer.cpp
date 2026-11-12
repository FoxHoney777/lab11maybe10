#include "Computer.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

Computer::Computer(string name, string os, const IDisk& disk)
    : name_(name), os_(os), mainDisk(disk.clone()) {
}

Computer::~Computer() {
    delete mainDisk;
}

void Computer::setMainDisk(const IDisk& disk) {
    delete mainDisk;
    mainDisk = disk.clone();
}

double Computer::getTotalCapacity() {
    if (mainDisk != nullptr) {
        return mainDisk->getCapacity();
    }
    return 0;
}

double Computer::getTotalUsed() {
    if (mainDisk != nullptr) {
        return mainDisk->getUsedSpace();
    }
    return 0;
}

void Computer::info() {
    cout << "Computer: " << name_ << " (" << os_ << ")\n";
    if (mainDisk) {
        cout << "Main disk: " << mainDisk->getName()
            << " | " << mainDisk->getCapacity() << "Gb"
            << " | used " << mainDisk->getUsedPercent() << "%\n";
    }
    cout << "  Total capacity: " << getTotalCapacity() << "Gb\n";
    cout << "  Total used:     " << getTotalUsed() << "Gb\n";

    cout << "---Disk info---" << endl;
    if (mainDisk) {
        mainDisk->getInfoD();
    }
    else {
        cout << "No disk installed\n";
    }
}

//новые поля
bool Computer::changeDiskName(string newName) {
    if (!mainDisk) return false;
    mainDisk->setName(newName);   // setName есть у IDisk — без приведения
    return true;
}

bool Computer::changeDiskStatus(bool status) {
    if (!mainDisk) return false;
    mainDisk->setStatus(status);
    return true;
}

// ---------- Уникальные параметры: нисходящее приведение ----------

bool Computer::changeHardDiskRpm(int rpm) {
    if (!mainDisk) return false;
    if (dynamic_cast<NetworkDisk*>(mainDisk)) return false;
    HardDisk* hdd = dynamic_cast<HardDisk*>(mainDisk);
    if (!hdd) return false;
    hdd->setRpm(rpm);
    return true;
}

bool Computer::changeSystemDiskSystemSize(double size) {
    if (!mainDisk) return false;
    SystemDisk* sd = dynamic_cast<SystemDisk*>(mainDisk);
    if (!sd) return false;
    sd->setSystemSize(size);
    return true;
}

bool Computer::changeNetworkDiskServer(string server) {
    if (!mainDisk) return false;
    NetworkDisk* nd = dynamic_cast<NetworkDisk*>(mainDisk);
    if (!nd) return false;
    nd->setServer(server);
    return true;
}

Computer* Computer::create(const string& name, const string& os, const IDisk& disk) {
    return new Computer(name, os, disk);
}