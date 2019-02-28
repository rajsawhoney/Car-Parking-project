//#include<bits/stdc++.h>
#include <iostream>
using namespace std;
class TypeError
{
    char msg[100];

  public:
    TypeError(char s[])
    {
        strcpy(msg, s);
    }
    void showError()
    {
        cout << msg << " Please enter valid type" << endl;
        exit(1);
    }
};

class Negative
{
    char msg[100];

  public:
    Negative(char s[])
    {
        strcpy(msg, s);
    }
    void showError()
    {
        cout << msg << " Please enter +ve datas!" << endl;
        return;
    }
};

class Invalid
{
    char msg[100];

  public:
    Invalid(char s[])
    {
        strcpy(msg, s);
    }
    void showError()
    {
        cout << msg << " Please enter valid data!" << endl;
         return;
    }
};

class Date
{
  private:
    int year, month, day;

  public:
    Date()
    {
    }
    Date(int netTime)
    {
        year = netTime / (24 * 360);
        month = (int(netTime) % (24 * 360)) / (30 * 24);
        day = ((int(netTime) % (24 * 360)) % (30 * 24)) / 24;
    }
    void set_date()
    {
    again:
        try
        {
            cout << "YYYY:MM:DD\n";
            cin >> year>>month>>day;
            cin.clear();        
            if (!static_cast<int>(year) || !static_cast<int>(month) || !static_cast<int>(day))
                throw TypeError("Type Error.");
            if (year < 0 || month < 0 || day < 0)
                throw Negative("Negative date entered!!");
            if (year < 1000 || month > 12 || day > 32)
                throw Invalid("Invalid date entered!!");
            
        }
        catch (TypeError t)
        {
            t.showError();
            goto again;
        }
        catch (Negative n)
        {
            n.showError();
            goto again;
        }
        catch (Invalid t)
        {
            t.showError();
            goto again;
        }
    }
    int operator-(Date d2)
    {
        Date d;
        int total_days;
        total_days = (year * 360 + month * 30 + day) - (d2.year * 360 + d2.month * 30 + d2.day);
        d.year = total_days / 360;
        d.month = (total_days % 360) / 30;
        d.day = (total_days % 360) % 30;
        return d.year * 360 * 24 + d.month * 30 * 24 + d.day * 24;
    }

    void displayDate()
    {
        char m = ' ', d = ' ';
        if (month < 10)
            m = '0';
        if (day < 10)
            d = '0';
        cout << "Date: " << year << " / " << m << month << " / " << d << day << endl;
    }

    void displaynetDate()
    {
        cout << year << " Years " << month << " Months " << day << " Days" << endl;
    }
};

class Time
{
  private:
    int hour, min, sec;
    string format;

  public:
    Time()
    {
    }
    Time(float netTime)
    {
        hour = netTime / 3600;
        min = (int(netTime) % 3600) / 60;
        sec = (int(netTime) % 3600) % 60;
    }

    void set_time()
    {
    again:
        try
        {
            cout << "HH:MM:SS\n";
            cin >> hour >> min >> sec;
            cout << "Enter the Time format AM/PM: ";
            if (hour < 0 || min < 0 || sec < 0)
                throw Negative("Negative time entered!!");
            if (hour > 12 || min > 59 || sec > 59)
                throw Invalid("Invalid time entered!!");
            cin.clear();
            if (!static_cast<int>(hour) || !static_cast<int>(min) || !static_cast<int>(sec))
                throw TypeError("Type Error.");

            cin >> format;
            transform(format.begin(), format.end(), format.begin(), ::toupper);
        }
        catch (TypeError t)
        {
            t.showError();
            goto again;
        }
        catch (Negative n)
        {
            n.showError();
            goto again;
        }
        catch (Invalid t)
        {
            t.showError();
            goto again;
        }
    }

    float operator-(Time t2)
    {
        Time t;
        int total_sec;
        total_sec = ((12 + hour) * 3600 + min * 60 + sec) - (t2.hour * 3600 + t2.min * 60 + t2.sec);
        t.hour = total_sec / 3600;
        t.min = (total_sec % 3600) / 60;
        t.sec = (total_sec % 3600) % 60;
        if (t2.hour == 12 && t2.format == format)
            return 12 + t.hour + t.min / 60.0 + t.sec / 3600.0;
        else if (t2.hour > hour && format == t2.format)
            return 12 + t.hour + t.min / 60.0 + t.sec / 3600.0;
        else
            return t.hour + t.min / 60.0 + t.sec / 3600.0;
    }

    void displayTime()
    {
        char flag[2];
        char h = ' ', m = ' ', s = ' ';
        if (format == "PM")
            strcpy(flag, "PM");
        else
            strcpy(flag, "AM");
        if (hour < 10)
            h = '0';
        if (min < 10)
            m = '0';
        if (sec < 10)
            s = '0';
        cout << "Time: " << h << hour << ":" << m << min << ":" << s << sec << " " << flag << endl;
    }

    void displaynetTime()
    {
        cout << hour << " Hours " << min << " Minutes " << sec << " Seconds" << endl;
    }
};
