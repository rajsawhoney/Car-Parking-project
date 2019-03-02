//This is the store house of this program Car Parking

#include <ctime>            //used for getting local date and time
#include "timeConversion.h" //user defined header file to convert date and time in seconds into date and time format
#include "date_time.h"      //user defined header file for getting date and time manually

class ParkingLotControl
{
  private:
    //For manual date and time
    Time entry_time, exit_time; //Created two objects of class Time
    Date entry_date, exit_date; //Created two objects of class Date

    //For system date and time
    string Entry, Exit;

    string carId;
    string name;
    float Pcharge;
    

  public:
    static int total_car_parked;    
    bool entryStatus = false, exitStatus = false;
    bool isSystem = false; //to work a/c to date and time mode
    bool usingSystem = false;
    bool isLotEmpty=true;
    void get_entry();
    void putcarId(string Id);
    double checkTime();
    void get_exit();
    int checkDate();
    float CheckTime();
    void calCharge();
    void showTotalTime();
    void showTotalCarParked();
    void showCharge();
    void removeCar();
    void operator++();
    void operator--();
    static int getTotalCar();
    string getCarId();
} c; //A class obj created
