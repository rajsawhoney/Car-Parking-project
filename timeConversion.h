#include <iostream>
using namespace std;

class DateTime
{
  private:
    int year = 0, mon = 0, day = 0, hour, min, sec;

  public:
    DateTime()
    {
    }

    DateTime(long tsec)
    {
        hour = tsec / 3600;
        min = (tsec % 3600) / 60;
        sec = (tsec % 3600) % 60;
        if (hour > 24)
        {
            year = hour / (24 * 360);
            mon = (hour % (24 * 360)) / (24 * 30);
            day = ((hour % (24 * 360)) % (24 * 30));
        }
    }
    void show()
    {
        if (hour > 24)
            cout << year << " Years " << mon << " months " << day << " days" << endl;
        cout << hour << " hours " << min << " mins " << sec << " secs" << endl;
    }
};