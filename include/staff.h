#include<iostream>
#include "/Users/UT20449257/Desktop/StaffManagement/include/hod.h"
using namespace std;

class Staff:public HoD{
    int StaffID;
    string firstName;
    string email;
    string password;

public:
    void staffLogin();        // handles staff login credentials
    void staffDashboard();    //handle staff dashboard
    void DisplayDetails();    // displays the all contents of a staff data csv file
    void RaiseRequest();      // use to raise a request to admin
};
