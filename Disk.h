#pragma once
#include <string>
#include <stdexcept>

//Exception
class EmptyNameException : public std::exception {
private:
    std::string message;
public:
    EmptyNameException() {
        message = "The disk name cannot be empty!";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class IDisk {

protected:

    std::string* name;
    int* capacity;
    int* usedSpace;
    bool* status;

public:

    IDisk();
    virtual ~IDisk();
    void mess(const std::string& methodName);

    virtual void setName(std::string name);
    virtual void setCapacity();
    void setUsedSpace();
    void setStatus(bool status);

    virtual std::string getName() = 0;
    virtual int getCapacity() = 0;
    virtual int getUsedSpace() = 0;
    virtual int getFreeSpace() = 0;
    virtual bool getStatus() = 0;
    virtual double getUsedPercent() = 0;

    void setCapacity(int value);
    void setUsedSpace(int value);


    virtual void getInfoD() = 0;
    IDisk(const IDisk& other);

    virtual IDisk* clone() const = 0;

};

// -------- HDD --------
class HardDisk : public IDisk {
private:
    int rpm;
public:
    std::string getName() override;
    int getCapacity() override;
    int getUsedSpace() override;
    int getFreeSpace() override;
    bool getStatus() override;
    double getUsedPercent() override;
    void getInfoD() override;

    int  getRpm();
    void setRpm(int rpm_);

    IDisk* clone() const override;
};


// -------- System --------
class SystemDisk : public IDisk {
private:
    int systemSize;
public:
    void setCapacity() override;

    std::string getName() override;
    int getCapacity() override;
    int getUsedSpace() override;
    int getFreeSpace() override;
    bool getStatus() override;
    double getUsedPercent() override;
    double getSystemSize();
    void   setSystemSize(double size);
    void getInfoD() override;
    IDisk* clone() const override;
};


// -------- External --------
class NetworkDisk : public HardDisk {
private:
    std::string server;
public:
    ~NetworkDisk() override;
    std::string getServer();
    void setServer(std::string server);

    IDisk* clone() const override;
    void getInfoD() override;
};



