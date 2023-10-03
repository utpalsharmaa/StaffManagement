#include <iostream>
#include <string>
#include <fstream>

#ifndef ADMIN_H
#define ADMIN_H

using namespace std;

class HoD
{
    int StaffID;
    string firstName;
    string lastName;
    string email;
    string phoneNo;
    string qualification;
    string designation;

public:
    void adminLogin();
    void adminDashboard();  // handles admin login credentials
    void AddStaff();      // implements adding staff data functionality into a csv file
    void DisplayStaff();    // displays the all contents of a staff data csv file
    void SearchStaff(string id);   // Function to search and display staff data from a CSV file
    void UpdateStaff();  // implements updating staff data functionality into a csv file
    void RemoveStaff();  // implements deleting staff data functionality from a csv file
    void ViewRequest();  // implements to view the request by staff 
};
#endif // ADMIN_H
