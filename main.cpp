#include <iostream>
#include <stdexcept> // Include the necessary header for exceptions
#include "/Users/UT20449257/Desktop/StaffManagement/include/hod.h"
#include "/Users/UT20449257/Desktop/StaffManagement/include/staff.h"

using namespace std;

int main()
{
    try
    {
        HoD hod;
        Staff staff;
        int choice;

        cout << "\n═══════════════════════════════════════════════════════" << endl;
        cout << "           XYZ College of Engineering                   " << endl;
        cout << "═══════════════════════════════════════════════════════\n" << endl;
        cout << "\n\t\t Welcome To XYZ College  " << endl;
        cout << "\n\t\tEnter 1  HoD Login" << endl;
        cout << "\t\tEnter 2  Staff Login" << endl;
        cout << "\t\tEnter 3  Exit" << endl; // Corrected the choice number
        cout << "\nPlease Enter Your Choice : ";

      
         while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nPlease enter a number!!" << endl;
            cout << "\nPlease Enter Your Choice : ";
        }
        switch (choice)
        {
        case 1:
            hod.adminLogin();
            break;
        case 2:
            staff.staffLogin();
            break;
        case 3:
            cout << "See you again." << endl;
            break;
        default:
            cout<<"Invalid Choice. Please enter a number between 1 and 3:";
            break;
        }
    }
    catch (const exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
    return 0;
}
