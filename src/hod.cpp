#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <random>
#include <regex>
#include <exception>
#include "/Users/UT20449257/Desktop/StaffManagement/include/hod.h"
using namespace std;
int loginCount = 0;
void HoD::adminLogin()
{
    string userId = "Utpal";
    string password = "12345";
    string id, pass;
    cout << "\n\nPlease Enter Your Username & Password For Authentiocation" << endl;

    try
    {
        cout << "\nEnter Your Username : ";
        cin >> id;

        cout << "\nEnter Your Password : ";
        cin >> pass;

        while (id != userId || pass != password)
        {
            cout << "\n!!!Login Error!!!" << endl;
            cout << "Please check your username or password again\n"
                 << endl;

            loginCount++;
            if (loginCount == 3)
            {
                cout << "ACCESS DENIED" << endl;
                cout << "You have reached your limit." << endl;
                exit(1);
            }

            cout << "\nEnter Your Username : ";
            cin >> id;
            cout << "\nEnter Your Password : ";
            cin >> pass;
        }
    }

    catch (exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }

    cout << "\nCongratulations " << userId << endl;
    cout << "Your login as HoD is successful.\n"
         << endl;
    adminDashboard();
}
void HoD::adminDashboard()
{
    string staffid;
    try
    {
        cout << "\n═══════════════════════════════════════════════════════" << endl;
        cout << "            Staff Management System Dashboard          " << endl;
        cout << "═══════════════════════════════════════════════════════\n"
             << endl;
        cout << "\tEnter 1  To Add New Staff" << endl;
        cout << "\tEnter 2  To Display Staff details" << endl;
        cout << "\tEnter 3  To Search for Staff" << endl;
        cout << "\tEnter 4  To Update Staff Information" << endl;
        cout << "\tEnter 5  To Removing Staff" << endl;
        cout << "\tEnter 6  To View Request" << endl;
        cout << "\tEnter 7  To Quit From This Session" << endl;
        cout << "\n═══════════════════════════════════════════════════════" << endl;

        int choice;
        cout << "\n\nPlease enter your choice : ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 7)
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nInvalid input. Please enter a number between 1 and 7: ";
            cin >> choice;
        }
        switch (choice)
        {
        case 1:
            AddStaff();
            adminDashboard();
            break;

        case 2:
            DisplayStaff();
            adminDashboard();
            break;
        case 3:
            cout << "Enter the staff id to search::";
            cin >> staffid;
            SearchStaff(staffid);
            adminDashboard();
            break;
        case 4:
            UpdateStaff();
            adminDashboard();
            break;
        case 5:
            RemoveStaff();
            adminDashboard();
            break;
        case 6:
            ViewRequest();
            adminDashboard();
            break;
        case 7:
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

bool isValidPhoneNumber(const string &phoneNumber)
{
    regex phonePattern(R"(\d{10})");
    return regex_match(phoneNumber, phonePattern);
}
bool isAlpha(const string &str)
{
    return all_of(str.begin(), str.end(), ::isalpha);
}

bool isValidEmail(const string &email)
{
    regex emailPattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)");
    return regex_match(email, emailPattern);
}
string generatePass(int length)
{
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int charLen = characters.length();

    string Pass;
    for (int i = 0; i < length; ++i)
    {
        int randomIndex = rand() % charLen;
        Pass += characters[randomIndex];
    }

    return Pass;
}

void HoD::AddStaff()
{
    try
    {
        srand(time(nullptr));
        // Generate a random number between 1 and 100
        StaffID = rand() % 100 + 1000;

        string randomPassword = generatePass(8);
        cin.ignore(256, '\n');

        cout << "Enter staff first name: ";
        while (!(cin >> firstName) || !isAlpha(firstName))
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a valid name: ";
        }
        firstName[0] = toupper(firstName[0]);

        cout << "Enter staff last name: ";
         while (!(cin >> lastName) || !isAlpha(lastName))
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a valid name: ";
        }
        lastName[0] = toupper(lastName[0]);
        cin.ignore(256, '\n');

        cout << "Enter staff email: ";
        cin >> email;
        while (!isValidEmail(email))
        {
            cout << "Invalid email format. Please enter a valid email: ";
            cin >> email;
        }

        cout << "Enter staff phone number: ";
        cin >> phoneNo;
        while (!isValidPhoneNumber(phoneNo))
        {
            cout << "Invalid phone number format. Please enter a valid phone number: ";
            cin >> phoneNo;
        }

        cout << "Enter staff qualification: ";
        while (!(cin >> qualification) || !isAlpha(qualification))
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a valid qulification: ";
        }

        cout << "Enter staff designation: ";
         while (!(cin >> designation) || !isAlpha(designation))
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a valid designation: ";
        }

        ofstream f1("//Users/UT20449257/Desktop/StaffManagement/data/Staff.csv", ios::app);
        ofstream f11("//Users/UT20449257/Desktop/StaffManagement/data/StaffLogin.csv", ios::app);

        f1 << StaffID << "," << firstName << "," << lastName << "," << email << "," << phoneNo << "," << qualification << "," << designation << endl;
        f11 << StaffID << "," << randomPassword << "," << firstName << endl;
        cout << "\nStaff record has been added successfully.\n"
             << endl;

        string opt;
        cout << "\nDo you want to add another staff details (yes/no) : ";
        cin >> opt;

        while (true)
        {
            transform(opt.begin(), opt.end(), opt.begin(), ::tolower);

            if (opt == "yes")
            {
                AddStaff();
                break;
            }
            else if (opt == "no")
            {
                // adminModules(); // Replace this with appropriate function call
                break;
            }
            else
            {
                cout << "Invalid input. Please enter 'yes' or 'no': ";
                cin >> opt;
            }
        }
    }
    catch (exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}

void HoD::DisplayStaff()
{
    try
    {
        ifstream file("/Users/UT20449257/Desktop/StaffManagement/data/Staff.csv");
        if (!file.is_open())
        {
            throw runtime_error("Error opening file: Staff.csv");
        }

        cout << "Below are the list of staff" << endl;

        cout << setw(10) << "Staff ID" << setw(20) << "First Name" << setw(20) << "Last Name"
             << setw(30) << "Email" << setw(15) << "Phone No" << setw(30) << "Qualification"
             << setw(20) << "Designation" << endl;

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string staffId, firstName, lastName, email, phoneNo, qualification, designation;

            getline(ss, staffId, ',');
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, email, ',');
            getline(ss, phoneNo, ',');
            getline(ss, qualification, ',');
            getline(ss, designation, ',');

            // Output each column with appropriate formatting
            cout << setw(10) << staffId << setw(20) << firstName << setw(20) << lastName
                 << setw(30) << email << setw(15) << phoneNo << setw(30) << qualification
                 << setw(20) << designation << endl;
        }
        file.close();

        string choice;

        cout << "\nDo you want to continue with the session (yes/no): ";
        cin >> choice;

        // Input validation for choice
        while (true)
        {
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == "yes")
            {
                // Call the appropriate function for further actions
                // adminModules();
                break;
            }
            else if (choice == "no")
            {
                cout << "See you again" << endl;
                break;
            }
            else
            {
                cout << "Invalid input. Please enter 'yes' or 'no': ";
                cin >> choice;
            }
        }
    }
    catch (const exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}

void HoD::SearchStaff(string id)
{
    try
    {
        ifstream file("/Users/UT20449257/Desktop/StaffManagement/data/Staff.csv");
        if (!file.is_open())
        {
            throw runtime_error("Error opening file: Staff.csv");
        }

        bool found = false;
        cout << "Below are the details of the staff with Staff ID " << id << endl;

        cout << setw(10) << "Staff ID" << setw(20) << "First Name" << setw(20) << "Last Name"
             << setw(30) << "Email" << setw(15) << "Phone No" << setw(20) << "Qualification"
             << setw(20) << "Designation" << endl;

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string staffId, firstName, lastName, email, phoneNo, qualification, designation;

            getline(ss, staffId, ',');
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, email, ',');
            getline(ss, phoneNo, ',');
            getline(ss, qualification, ',');
            getline(ss, designation, ',');

            // string staffID = staffId;
            if (staffId == id)
            {
                found = true;

                // Output each column with appropriate formatting
                cout << setw(10) << staffId << setw(20) << firstName << setw(20) << lastName
                     << setw(30) << email << setw(15) << phoneNo << setw(20) << qualification
                     << setw(20) << designation << endl;

                break; // Found the staff, exit the loop
            }
        }
        file.close();

        if (!found)
        {
            cout << "Staff with ID " << id << " not found." << endl;
        }

        string choice;

        cout << "\nDo you want to continue with the session (yes/no): ";
        cin >> choice;

        // Input validation for choice
        while (true)
        {
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == "yes")
            {
                // Call the appropriate function for further actions
                // adminModules();
                break;
            }
            else if (choice == "no")
            {
                cout << "See you again" << endl;
                break;
            }
            else
            {
                cout << "Invalid input. Please enter 'yes' or 'no': ";
                cin >> choice;
            }
        }
    }
    catch (const exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}

void HoD::UpdateStaff()
{
    string filename = "/Users/UT20449257/Desktop/StaffManagement/data/Staff.csv";
    try
    {
        ifstream fin(filename);
        if (!fin)
        {
            throw runtime_error("File not found!");
        }

        string id;
        cout << "Enter the id:";
        cin >> id;

        vector<vector<string>> matchedRows; // To store rows with matching ID
        string line;

        while (getline(fin, line))
        {
            vector<string> row;
            stringstream ss(line);
            string cell;
            while (getline(ss, cell, ','))
            {
                row.push_back(cell);
            }
            matchedRows.push_back(row);
        }

        fin.close(); // Close the file

        cout << "Select a detail to update:\n";
        cout << "1. First Name\n";
        cout << "2. Last Name\n";
        cout << "3. Email\n";
        cout << "4. Phone Number\n";
        cout << "5. Qualification\n";
        cout << "6. Designation\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        string s1;
        cout << "Enter Detail to be updated: ";
        cin >> s1;

        for (vector<vector<string>>::size_type i = 0; i < matchedRows.size(); i++)
        {
            if (matchedRows[i][0] == id)
            {
                if (choice >= 1 && choice <= matchedRows[i].size())
                {
                    matchedRows[i][choice] = s1;

                    ofstream fout(filename);
                    for (vector<vector<string>>::size_type j = 0; j < matchedRows.size(); j++)
                    {
                        for (vector<string>::size_type k = 0; k < matchedRows[j].size(); k++)
                        {
                            fout << matchedRows[j][k];
                            if (k != matchedRows[j].size() - 1)
                            {
                                fout << ",";
                            }
                        }
                        fout << endl;
                    }
                    fout.close();
                    break;
                }
                else
                {
                    throw out_of_range("Invalid choice.");
                }
            }
        }

        string opt;
        cout << "\nDo you want to update another staff details (yes/no): ";
        cin >> opt;
        transform(opt.begin(), opt.end(), opt.begin(), ::tolower);

        while (true)
        {
            if (opt == "yes")
            {
                UpdateStaff();
                break;
            }
            else if (opt == "no")
            {
                // adminModules(); // Replace with appropriate function call
                break;
            }
            else
            {
                cout << "Invalid input. Please enter 'yes' or 'no': ";
                cin >> opt;
            }
        }
    }
    catch (const exception &e)
    {
        cout << "An error occurred: " << e.what() << endl;
    }
}

void HoD::RemoveStaff()
{
    try
    {
        int searchStaffID;
        cout << "Enter the Staff ID of the staff to delete data: ";
        while (!(cin >> searchStaffID) || cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a valid Staff ID: ";
        }
        cin.ignore(256, '\n');

        ifstream inputFile("/Users/UT20449257/Desktop/StaffManagement/data/Staff.csv");
        ofstream tempFile("/Users/UT20449257/Desktop/StaffManagement/data/temp.csv");

        ifstream inputFile1("/Users/UT20449257/Desktop/StaffManagement/data/StaffLogin.csv");
        ofstream tempFile1("/Users/UT20449257/Desktop/StaffManagement/data/temp1.csv");

        bool found = false;
        int foundStaffID = -1; // Initialize to an invalid value
        string line;

        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string column;
            int staffID;

            if (getline(ss, column, ','))
            {
                try
                {
                    staffID = stoi(column);

                    if (staffID == searchStaffID)
                    {
                        found = true;
                        foundStaffID = staffID;
                        cout << "Staff found with ID " << searchStaffID << ". Data deleted." << endl;
                    }
                    else
                    {
                        // Write the original data to temp file
                        tempFile << line << endl;
                    }
                }
                catch (const invalid_argument &ex)
                {
                    cerr << "Invalid staff ID format: " << column << endl;
                    // Handle the error here, such as skipping the line or displaying an error message
                }
            }
        }
        inputFile.close();
        tempFile.close();

        while (getline(inputFile1, line))
        {
            stringstream ss(line);
            string column;
            int staffID;

            if (getline(ss, column, ','))
            {
                try
                {
                    staffID = stoi(column);

                    if (staffID != foundStaffID)
                    {
                        // Write the original data to temp file
                        tempFile1 << line << endl;
                    }
                }
                catch (const invalid_argument &ex)
                {
                    cerr << "Invalid staff ID format: " << column << endl;
                    // Handle the error here, such as skipping the line or displaying an error message
                }
            }
        }
        inputFile1.close();
        tempFile1.close();

        if (!found)
        {
            cout << "Staff with ID " << searchStaffID << " not found." << endl;
        }
        else
        {
            // Rename the temp files to replace the original files
            remove("/Users/UT20449257/Desktop/StaffManagement/data/Staff.csv");
            rename("/Users/UT20449257/Desktop/StaffManagement/data/temp.csv", "/Users/UT20449257/Desktop/StaffManagement/data/Staff.csv");

            remove("/Users/UT20449257/Desktop/StaffManagement/data/StaffLogin.csv");
            rename("/Users/UT20449257/Desktop/StaffManagement/data/temp1.csv", "/Users/UT20449257/Desktop/StaffManagement/data/StaffLogin.csv");

            cout << "Staff data deleted successfully." << endl;
        }

        string opt;
        cout << "\nDo you want to delete staff data again (yes/no): ";
        cin >> opt;
        transform(opt.begin(), opt.end(), opt.begin(), ::tolower);

        while (true)
        {
            if (opt == "yes")
            {
                RemoveStaff();
                break;
            }
            else if (opt == "no")
            {
                adminDashboard(); // Replace with appropriate function call
                break;
            }
            else
            {
                cout << "Invalid input. Please enter 'yes' or 'no': ";
                cin >> opt;
            }
        }
    }
    catch (const exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}

void HoD::ViewRequest()
{
    string filename = "/Users/UT20449257/Desktop/StaffManagement/data/Requests.txt";
    try
    {
        ifstream fin(filename);
        if (!fin)
        {
            throw runtime_error("File not found!");
        }

        string line;
        while (getline(fin, line))
        {
            cout << line << endl;
        }

        fin.close();

        string opt;
        cout << "\nDo you want to view requests again (yes/no): ";
        cin >> opt;
        transform(opt.begin(), opt.end(), opt.begin(), ::tolower);

        while (true)
        {
            if (opt == "yes")
            {
                ViewRequest();
                break;
            }
            else if (opt == "no")
            {
                adminDashboard(); // Replace with appropriate function call
                break;
            }
            else
            {
                cout << "Invalid input. Please enter 'yes' or 'no': ";
                cin >> opt;
            }
        }
    }
    catch (const exception &e)
    {
        cout << "An error occurred: " << e.what() << endl;
    }
}
