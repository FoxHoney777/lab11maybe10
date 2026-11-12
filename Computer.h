
#pragma once
#include <string>
#include "Disk.h"


class Computer {
private:
    std::string name_;
    std::string os_;
    IDisk* mainDisk = nullptr;
public:
    Computer(std::string name, std::string os, const IDisk& disk);
    ~Computer();
    void setMainDisk(const IDisk& disk);
    double getTotalCapacity();
    double getTotalUsed();
    void info();

    //ќбщие параметры 
    bool changeDiskName(std::string newName);
    bool changeDiskStatus(bool status);

    //”никальные 
    bool changeHardDiskRpm(int rpm);
    bool changeSystemDiskSystemSize(double size);
    bool changeNetworkDiskServer(std::string server);



    static Computer* create(const std::string& name,
        const std::string& os,
        const IDisk& disk);
};
