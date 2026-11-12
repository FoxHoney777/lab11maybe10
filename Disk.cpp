#include <iostream>
#include <string>
#include <ctime>
#include "Disk.h"
#include <stdexcept>

IDisk::IDisk() {
	name = new std::string("Unknown");
	status = new bool(false);
	capacity = new int(0);
	usedSpace = new int(0);
}

IDisk::~IDisk() {
	std::cout << "[DISK] Annihilation for \\" << *name << std::endl;
	delete name;
	delete capacity;
	delete usedSpace;
	delete status;
}

IDisk::IDisk(const IDisk& other)
	: name(new std::string(*other.name)),
	status(new bool(*other.status)),
	capacity(new int(*other.capacity)),
	usedSpace(new int(*other.usedSpace)) {
}

void IDisk::mess(const std::string& methodName) {
	std::cout << "\nProgramm " << methodName << "() called\n";
}
//exception
void IDisk::setName(std::string name) {
	if (name.empty()) {
		throw EmptyNameException();
	}
	*this->name = name;
}

void IDisk::setCapacity() {
	static const int sizes[6] = { 128, 256, 512, 1024, 2048, 4096 };
	*this->capacity = sizes[rand() % 6];
}

void IDisk::setUsedSpace() {
	int used;
	if (*capacity > 0) {
		used = rand() % (*capacity);
	}
	else used = 0;
	*this->usedSpace = used;
}

void IDisk::setStatus(bool status) {
	*this->status = status;
}
//exception 
void IDisk::setCapacity(int value) {
	if (value < 0) {
		throw std::out_of_range("Error: volume cannot be negative");
	}
	if (value > 10000) {
		throw std::out_of_range("Error: disk capacity too large");
	}
	*capacity = value;
}

void IDisk::setUsedSpace(int value) {
	*usedSpace = value;
}

// -------- HDD --------
std::string HardDisk::getName() {
	return *name;
}

int HardDisk::getCapacity() {
	return *capacity;
}

int HardDisk::getUsedSpace() {
	return *usedSpace;
}

int HardDisk::getFreeSpace() {
	return *capacity - *usedSpace;
}

bool HardDisk::getStatus() {
	return *status;
}

double HardDisk::getUsedPercent() {
	if (*capacity == 0) return 0.0;
	double base = 100.0 * (*usedSpace) / (*capacity);
	if (base > 95.0) return 95.0;   // 5% под служебные нужды
	return base;
}
int HardDisk::getRpm() {
	return rpm;
}
void HardDisk::setRpm(int rpm) {
	this->rpm = rpm;
}

void HardDisk::getInfoD() {
	std::cout << "<---Hard disk--->\n";
	std::cout << "Name:\t" << getName() << std::endl;
	std::cout << "Capacity:\t" << getCapacity() << " Gb." << std::endl;
	std::cout << "Used:\t" << getUsedSpace() << " Gb. => "
		<< getUsedPercent() << " %." << std::endl;
	std::cout << "Free:\t" << getFreeSpace() << " Gb." << std::endl;
	std::cout << "Status:\t" << (getStatus() ? "On" : "False") << std::endl;
	std::cout << "Rom:\t" << getRpm() << std::endl;
}

IDisk* HardDisk::clone() const {
	return new HardDisk(*this);   // копируем текущий объект
}


// -------- System --------
void SystemDisk::setCapacity() {
	*capacity = 512;
}

std::string SystemDisk::getName() {
	return *name;
}

int SystemDisk::getCapacity() {
	return *capacity;
}

int SystemDisk::getUsedSpace() {
	return *usedSpace;
}

int SystemDisk::getFreeSpace() {
	return *capacity - *usedSpace;
}

bool SystemDisk::getStatus() {
	return *status;
}

double SystemDisk::getUsedPercent() {
	if (*capacity == 0) return 0.0;
	return 100.0 * (*usedSpace) / (*capacity);
}

double SystemDisk::getSystemSize() {
	return systemSize;
}

void  SystemDisk::setSystemSize(double size) {
	this->systemSize = size;
}

void SystemDisk::getInfoD() {
	std::cout << "<---System disk--->\n";
	std::cout << "Name:\t" << getName() << std::endl;
	std::cout << "Capacity:\t" << getCapacity() << " Gb." << std::endl;
	std::cout << "Used:\t" << getUsedSpace() << " Gb. => "
		<< getUsedPercent() << " %." << std::endl;
	std::cout << "Free:\t" << getFreeSpace() << " Gb." << std::endl;
	std::cout << "Status:\t" << (getStatus() ? "On" : "False") << std::endl;
	std::cout << "SystemSize:\t" << getSystemSize() << std::endl;
}

IDisk* SystemDisk::clone() const {
	return new SystemDisk(*this);
}


// -------- External --------
NetworkDisk::~NetworkDisk() {
	std::cout << "[Security] blocking for " << *name << std::endl;
}
std::string NetworkDisk::getServer() {
	return server;
}
//test3 exception
void NetworkDisk::setServer(std::string server) {
	if (server.empty()) {
		throw std::invalid_argument("Empty");
	}
	
	this->server = server;
}

void NetworkDisk::getInfoD() {
	std::cout << "<---Network disk--->\n";
	std::cout << "Name:\t" << getName() << std::endl;
	std::cout << "Capacity:\t" << getCapacity() << " Gb." << std::endl;
	std::cout << "Used:\t" << getUsedSpace() << " Gb. => "
		<< getUsedPercent() << " %." << std::endl;
	std::cout << "Free:\t" << getFreeSpace() << " Gb." << std::endl;
	std::cout << "Status:\t" << (getStatus() ? "On" : "False") << std::endl;
	std::cout << "Server:\t" << getServer() << std::endl;
	std::cout << "Rom:\t" << getRpm() << std::endl;
}
IDisk* NetworkDisk::clone() const {
	return new NetworkDisk(*this);
}



