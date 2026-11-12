#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>
#include "Disk.h"
#include "Computer.h"

using namespace std;

//1. Программа на тематику "Диск"
//2. Автор: Ахмедова Рената, ПМИ-251
//3. Дата создания: долгие бессонные ночи / Версия: закончена 27.10.2026, Состояние: в разработке
//4. Использование программы разрешаю в любых целях, не нарушающих закон и не сеющих смуту
//5. Примечать пока нечего.

int main() {

    srand(time(NULL));
    //test exception 1
    SystemDisk* test1 = new SystemDisk();
    try {
        test1->setName("");
    }
    catch (const EmptyNameException& e) {
        std::cout << "Error: " << e.what() << std::endl;
        cout << endl;
    }
    //test exception 2
    try {
        test1->IDisk::setCapacity(-50);
    }
    catch (const std::out_of_range& e) {
        cout << "out_of_range: " << e.what() << endl;
        cout << endl;
    }
    delete test1;
    //test exception 3
    NetworkDisk* test3 = new NetworkDisk();
    try {   
        test3->setServer(""); 
    }
    catch (const std::invalid_argument& e) {
        cout << endl;
        cout << "invalid_argument: " << e.what() << endl;
        cout << endl;
    }
    delete test3;

    cout << "Choose disk type:\n";
    cout << "  1 - HardDisk\n";
    cout << "  2 - SystemDisk\n";
    cout << "  3 - NetworkDisk\n";
    cout << "Your choice: ";

    int choice;
    cin >> choice;

    string nameD;

   
    IDisk* virus = nullptr;
    switch (choice) {
    case 1: {
        virus = new HardDisk();
        nameD = "HardDisk";
        break;
    }
    case 2: {
        virus = new SystemDisk();
        nameD = "SystemDisk";
        break;
    }
    case 3: {
        virus = new NetworkDisk();
        nameD = "Cloud";
        break;
    }
    default:
        cout << "Wrong choice!\n Bye!\n";
        return -1;
    }

    virus->setName(nameD);
    virus->setCapacity();
    virus->setUsedSpace();
    virus->setStatus(true);

    cout << "PC info" << endl;
    Computer pc("Glavnya nya~", "Linuxoid", *virus);
    pc.info();
    cout << endl;

    //Изменение параметров
    cout << "\nChange disk info\n";
    if (pc.changeDiskName("Glavnya-2"))
        cout << "Name changed\n";
    if (pc.changeDiskStatus(false))
        cout << "Status changed to Off\n";
    //Уникальные
    cout << "\nChange unique disk info\n";
    if (pc.changeHardDiskRpm(5400))
        cout << "RPM changed to 5400\n";
    else if (pc.changeSystemDiskSystemSize(10))
        cout << "SystemSize changed to 10\n";
    else if (pc.changeNetworkDiskServer("cloud.example.com"))
        cout << "Server changed to cloud.example.com\n";
    else
        cout << "No unique\n";

    cout << "\nChanges:\n";
    pc.info();


    //Статический метод создания класса
    cout << "\n\n~~~~~~~ Computer (create) ~~~~~~~\n";
    Computer* pc2 = Computer::create("SteamPunk", "WINda", *virus);
    if (!pc2) {
        cout << "Failed to create computer\n";
    }
    else {
        pc2->changeDiskName("SteamPunk-DISK");
        pc2->info();

        if (pc2->changeNetworkDiskServer("fire.local"))
            cout << "Server changed via fire object\n";

        delete pc2;
    }

    delete virus;
}