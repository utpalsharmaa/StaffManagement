#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>
#include <regex>
#include <exception>
#include "/Users/UT20449257/Desktop/StaffManagement/include/staff.h"
int login = 0;
string loginId;
void Staff::staffLogin()
{
    string id, pass;
    cout << "\n\nPlease Enter Your Username & Password For Authentication" << endl;

    try
    {
        ifstream credentialsFile("/Users/UT20449257/Desktop/StaffManagement/data/StaffLogin.csv");
        if (!credentialsFile.is_open())
        {
            cerr << "Unable to open credentials file." << endl;
            return;
        }
        
        cout << "\nEnter Your Username : ";
        cin >> id;
        loginId = id;

        cout << "\nEnter Your Password : ";
        cin >> pass;

        bool loggedIn = false;
        string line;
        while (getline(credentialsFile, line))
        {
            stringstream ss(line);
            string userId, password, name;

            getline(ss, userId, ',');
            getline(ss, password, ',');
           

            if (userId == id && password == pass)
            {
                loggedIn = true;
                break;
            }
        }

        credentialsFile.close();

        if (!loggedIn)
        {
            cout << "\n!!!Login Error!!!" << endl;
            cout << "Please check your username or password again\n"
                 << endl;

            login++;
            if (login == 3)
            {
                cout << "ACCESS DENIED" << endl;
                cout << "You have reached your limit." << endl;
                exit(1);
            }

            staffLogin();
            return;
        }
    }
    catch (exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }

    cout << "\nCongratulations " << id << endl;
    cout << "Your login as staff is successful.\n"
         << endl;
    staffDashboard();
}
void Staff::staffDashboard()
{
    try
    {
        cout << "\n═══════════════════════════════════════════════════════" << endl;
        cout << "            Staff Management System Dashboard          " << endl;
        cout << "═══════════════════════════════════════════════════════\n"
             << endl;
        cout << "\tEnter 1  To View Details" << endl;
        cout << "\tEnter 2  To Raise Request" << endl;
        cout << "\tEnter 3  To Quit From This Session" << endl;
        cout << "\n═══════════════════════════════════════════════════════" << endl;

        int choice;
        cout << "\n\nPlease enter your choice : ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 3)
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nInvalid input. Please enter a number between 1 and 3: ";
            cin >> choice;
        }
        switch (choice)
        {
        case 1:
            DisplayDetails();
            staffDashboard();
            break;

        case 2:
            RaiseRequest();
            staffDashboard();
            break;

        case 3:
            cout << "Thank you, will see you soon." << endl;
            break;

        default:
            cout << "Please choose valid Option" << endl;
            break;
        }
    }
    catch (exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}

bool isValidAlpha(const string &input){
    for (char c : input){
        if (!isalpha(c)){
            return false;
        }
    }
    return true;
}

void Staff::DisplayDetails()
{
    SearchStaff(loginId);
}

void Staff::RaiseRequest()
{
    try
    {
        ofstream requestFile("/Users/UT20449257/Desktop/StaffManagement/data/Requests.txt", ios::app);
        if (!requestFile.is_open())
        {
            throw runtime_error("Error opening file: Requests.txt");
        }

        string requestDetails;
        cout << "Enter your request to update details for Staff ID " << loginId << ":" << endl;
        cin.ignore(); // Clear the newline character
        
        getline(std::cin, requestDetails);
        srand(time(nullptr));
        // Generate a random request ID
        int requestid = rand() % 100 + 1000;

        requestFile << "Request ID: " << requestid << "\n";
        requestFile << "Staff ID: " << loginId << "\n";
        requestFile << "Request: " << requestDetails << "\n";
        requestFile << "----------------------\n";

        requestFile.close();

        cout << "Request raised successfully! Your Request ID is: " << requestid << endl;
    }
    catch (const exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}