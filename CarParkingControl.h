#include <iostream>
#include <cstring> //used for string related operations
#include <fstream> //used for file handling purpose
#include <iomanip> //used for output formatting
#include <conio.h> //used for screen clearing purpose
#include "CarClass.h"
const char *filename = "MeroParkingFinal1.txt";
string DataBaseUsername="admin";
string DataBasePass = "password";
time_t entryT, exitT;
using namespace std;
void ParkingLotControl::removeCar()
{
    isLotEmpty=true;
    //entry_time.reset();
    //exit_time.reset();
    //entry_date.reset();
    //exit_date.reset();
    carId="None";
    entryStatus=false;
    exitStatus=false;
}
void ParkingLotControl::get_entry()
{
    int mode;
    Pcharge = 2; //Min parking charge
    isLotEmpty=false;
    cout << "Taking the entry records...\n";
    cout << "Enter the car owner name: ";
    cin >> name;
up:
    cout << "Choose Mode:::\n1--->System Date&Time Mode\n2--->Manual Date&Time Mode\n\n";
    cout << "Choose Date & Time Mode::\t";
    cin >> mode;
    if (mode == 1)
        isSystem = true;
    else if (mode == 2)
        isSystem = false;
    else
    {
        cout << "Invalid option selected!!! Try again...\n";
        goto up;
    }
    if (isSystem)
    {
        entryT = time(0)+20700; //added to compensate the time loss
        char *entryTime = ctime(&entryT);
        Entry = static_cast<string>(entryTime);
        usingSystem = true;
    }
    else
    {
        cout << "Enter the current date (Year/mon/day): " << endl;
        entry_date.set_date();
        cout << "Enter the current time: ";
        entry_time.set_time();
        usingSystem = false;
    }
    cout << "Entry records successfully noted..." << endl;
}

void ParkingLotControl::putcarId(string Id)
{
    carId = Id;
}

double ParkingLotControl::checkTime()
{
    return difftime(exitT, entryT) / 3600; //returns time diff in hours
}

void ParkingLotControl::get_exit()
{
    if (usingSystem == 1)
    {
        exitT = time(0)+20700;
        char *exitTime = ctime(&exitT);
        Exit = static_cast<string>(exitTime);
    }
    else
    {
        cout << "Taking exit date and time..." << endl;
        cout << "Enter the current date (Year/mon/day): " << endl;
        exit_date.set_date();
        cout << "Enter the current time: ";
        exit_time.set_time();
    }
    cout << "Exit records successfully noted..." << endl;
}

int ParkingLotControl::checkDate()
{
    return exit_date - entry_date; // returns date in hours
}

float ParkingLotControl::CheckTime()
{
    return exit_time - entry_time; // returns time in hours
}

void ParkingLotControl::calCharge()
{
    if (usingSystem == 1)
        goto system;
    else
    {
        float netDate;
        netDate = checkDate();
        if (netDate < 0)
        {
            cout << "Invalid date entered...." << endl;
            return;
        }

        else if (netDate == 0) //same day
        {
            if (CheckTime() < 0)
            {
                cout << "Invalid time entered..." << endl;
                return;
            }
            if (CheckTime() >= 3)
            {
                Pcharge = Pcharge + (CheckTime() - 3) * .5;
                return;
            }
        }
        else if (netDate == 24 && CheckTime() < 24)
        {
            Pcharge += (CheckTime() - 3) * .5;
            return;
        }
        else if (netDate > 24)
        {
            Pcharge = (netDate / 24) * 8;
            return;
        }
    }

system:
    double netTime;
    netTime = checkTime();
    if (netTime > 24)
    {
        Pcharge = (netTime / 24) * 8;
        return;
    }

    else if (netTime >= 3)
    {
        Pcharge += (netTime - 3) * .5;
        return;
    }
}

void ParkingLotControl::showTotalTime()
{
    if (usingSystem == 1)
    {
        DateTime converted;
        converted = difftime(exitT, entryT);
        if (exitStatus == 1)
            converted.show();
        else
            cout << "Exit records not taken yet..." << endl;
        return;
    }
    else
    {
        float netDate = checkDate();
        if (netDate < 0 || exitStatus == false)
        {
            cout << "Exit records not taken yet..." << endl;
            return;
        }
        else if (netDate == 0) //Car exit on the same day
        {
            Time t;
            t = CheckTime() * 3600; // converting basic type to class type
            t.displaynetTime();
            return;
        }
        else if (netDate == 24 && CheckTime() < 24)
        {
            Time t;
            t = CheckTime() * 3600; // converting basic type to class type
            t.displaynetTime();
            return;
        }
        else
        {
            Date d;
            d = checkDate(); // converting basic type to class type
            d.displaynetDate();
            return;
        }
    }
}

void ParkingLotControl::showTotalCarParked()
{    
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "\n\tEntry records and more info:" << endl;
    cout << "\n\tCar Owner: " << name << endl;
    cout << "\n\tCarID: " << carId << endl;

    if (usingSystem == 1)
    {
        cout << "\n\tEntry date & time: \n";
        cout << "\n\t";
        cout << Entry << endl;
        cout << "\n\tExit date & time: \n";
        cout << "\n\t";
        if (exitStatus == 1)
            cout << Exit << endl;
        cout << "\n\tTotal time of staying==";
        showTotalTime();
    }
    else
    {
        cout << "\n\tEntry date & time: \n";
        cout << "\n\t";
        entry_date.displayDate();
        cout << "\n\t";
        entry_time.displayTime();
        cout << "\n\tExit date & time: \n";
        if (exitStatus == 1)
        {
            cout << "\n\t";
            exit_date.displayDate();
            cout << "\n\t";
            exit_time.displayTime();
        }
        cout << "\n\tTotal time of staying==";
        showTotalTime();
    }
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void ParkingLotControl::showCharge()
{
    if (entryStatus == 1 && exitStatus == 1)
    {
        calCharge();
        cout << "Exit reports and more info:" << endl;
        cout << "Car Owner: " << name << endl;
        cout << "CarID: " << carId << endl;
        cout << "Entry date & time: \n";
        if (isSystem == 1)
            cout << Entry << endl;
        else
        {
            entry_date.displayDate();
            entry_time.displayTime();
        }
        cout << "Exit date & time:\n";
        if (isSystem == 1)
            cout << Exit << endl;
        else
        {
            exit_date.displayDate();
            exit_time.displayTime();
        }
        cout << endl
             << "Total staying time: " << endl;
        showTotalTime();
        cout << "Total Parking charge: "
             << " $ " << Pcharge << endl;
        cout << "Have a safe journey ahead...Happy Parking....!!!" << endl;
    }
    else
        cout << "Sir please departure the car first..." << endl;
    if (total_car_parked < 0)
        cout << "There's no any car parked in our Lot...." << endl;
}

void ParkingLotControl::operator++()
{
    ++total_car_parked;
}

void ParkingLotControl::operator--()
{
    --total_car_parked;
}

int ParkingLotControl::getTotalCar()
{
    return total_car_parked;
}
string ParkingLotControl::getCarId()
{
    return carId;
}

int ParkingLotControl::total_car_parked=0;

void delete_record()
{
    int found = 0;
    string carNo;
    cout << "\n\tEnter the car no you want to get departured : ";
    cin >> carNo;
    ifstream inFile;
    inFile.open(filename, ios::binary | ios::in);
    ofstream outFile;
    outFile.open("temp1.dat", ios::out | ios::binary);
    outFile.seekp(0, ios::beg);
    inFile.seekg(0, ios::beg);
    while (inFile.read((char *)&c, sizeof(c)))
    {
        if (c.getCarId() == carNo)
        {
            found = 1;
            break;
        }
    }
    if (found == 1)
    {
        if (c.getCarId() == carNo && c.exitStatus == false)
        {
            cout << "This car is not Departured from our DataBase yet...!!" << endl;
            return;
        }
        else
        {
            inFile.seekg(0, ios::beg);
            outFile.seekp(0, ios::beg);
            while (inFile.read((char *)&c, sizeof(c)))
            {
                if (c.getCarId() != carNo)
                    outFile.write((char *)&c, sizeof(c));
                if (c.getCarId() == carNo && c.exitStatus == 1)
                {
                    c.showCharge();
                    cout << "\n\t Car with Id " << carNo << " is successfully departured from our DateBase...\n\n";
                }
            }
            inFile.close();
            outFile.close();
            remove(filename);
            rename("temp1.dat", filename);
        }
    }
    else
        cout << "Car with this ID doesn't exist in our DataBase!!!\n\n";
}

void menu()
{
    cout << setfill('=') << setw(100);
    cout << "\n\t\t***CAR PARKING DATA BASE***";
    cout << setfill('=') << setw(100);
    cout << setfill('~') << setw(100) << endl;
    cout << "\n\n\t\t1-->Do entry the car" << endl;
    cout << "\t\t2-->Take departure" << endl;
    cout << "\t\t3-->Print the bill" << endl;
    cout << "\t\t4-->Info on all parked Cars" << endl;
    cout << "\t\t5-->Log Out" << endl
         << endl;
    cout << setfill('~') << setw(100) << endl;
    cout << "\n\t\tEnter your choice here==\t";
}

void LoginPanel()
{
    cout << "________________________________________________________________________" << endl;
    cout << setw(43) << "***WEL-COME To RAZZZ Car Parking Lot***" << endl;
    cout << "________________________________________________________________________" << endl
         << endl;
    cout << "________________________________________________________________________" << endl
         << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1->Login to your ParkingLot DataBase..." << endl;
    cout << "2->Change Your Password..." << endl;
    cout << "3->Exit from the Program" << endl;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "________________________________________________________________________" << endl;
}

bool checkLogin(string username,string pass)
 {
      if(DataBaseUsername==username && DataBasePass==pass)
           return true;
      else
          return false;    
    }

void changePass(string pass)
{
    DataBasePass = pass;
}

void changeUsername(string user)
{
    DataBaseUsername=user;
}