#include <bits/stdc++.h>
#include "User.h"
#include "Admin.h"

using namespace std;

void displayMainMenu() {
    cout << R"(

        █████   ███  ██████      ███████  ██████   ██████  ██████  ███████ 
       ██   ██ ██ ██      ██     ██      ██    ██ ██    ██ ██   ██ ██      
       ███████        █████      █████   ██    ██ ██    ██ ██   ██ ███████ 
       ██   ██            ██     ██      ██    ██ ██    ██ ██   ██      ██ 
       ██   ██       ██████      ██       ██████   ██████  ██████  ███████ 
                                                                    
                                                                    

        [1] Admin Login
        [2] User Login
        [3] Hotels
        [4] Delivery
        [5] Exit

        Enter your choice: )";
    // cout << "Main Menu:" << endl;
    // cout << "1. Admin" << endl;
    // cout << "2. User" << endl;
    // cout << "3. Hotel Management" << endl;
    // cout << "4. Delivery Service" << endl;
    // cout << "5. Exit" << endl;
    // cout << "Enter your choice: ";
}

namespace main_funcs {
    // Function to execute option 1
    void Admin() {
        cout << "Executing Option 1..." << endl;
        // Your logic for Option 1 goes here
        cout << "Option 1 executed!" << endl << endl;
    }

    // Function to execute option 2
    void User() {
        cout << "\t\t\t Welcome to User Login" << endl;
        cout << "\t\t\t 1. Login" << endl;
        cout << "\t\t\t 2. Register" << endl;
        cout << "\t\t\t 3. Forgot Password" << endl;
        cout << "\t\t\t 4. Exit" << endl;
        cout << "\t\t\t Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                user_funcs::login();
                break;
            case 2:
                user_funcs::registerUser();
                break;
            case 3:
                user_funcs::forgot();
                break;

            case 4:
                cout << R"(
                      ██████╗ ██╗   ██╗███████╗
                      ██╔══██╗╚██╗ ██╔╝██╔════╝
                      ██████╔╝ ╚████╔╝ █████╗  
                      ██╔══██╗  ╚██╔╝  ██╔══╝  
                      ██████╔╝   ██║   ███████╗
                      ╚═════╝    ╚═╝   ╚══════╝
                )" << endl;
                break;    
            default:
                // system("cls");
                cout << "Invalid choice. Please try again." << endl << endl;
                break;
        }
    }

    // Function to execute option 3
    void Hotel() {
        cout << "Executing Option 3..." << endl;
        // Your logic for Option 3 goes here
        cout << "Option 3 executed!" << endl << endl;
    }

    void Delivery() {
        cout << "Executing Option 4..." << endl;
        // Your logic for Option 4 goes here
        cout << "Option 4 executed!" << endl << endl;
    }
}

int main() {
    int choice;
    bool exit = false;

    while (!exit) {
        displayMainMenu();
        // if(!(cin >> choice)) {
        //     cout << "Invalid choice. Please try again." << endl << endl;
        //     cin.clear();
        //     cin.ignore(10000, '\n');
        //     continue;
        // }
        // cin >> choice;
        global_funcs::get_input(choice, "Enter your choice: ");

        switch (choice) {
            case 1:
                main_funcs::Admin();
                break;
            case 2:
                main_funcs::User();
                break;
            case 3:
                main_funcs::Hotel();
                break;
            case 4:
                main_funcs::Delivery();
                break;    
            case 5:
                exit = true;
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl << endl;
                break;
        }
    }

    return 0;
}


