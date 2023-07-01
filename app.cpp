#include <bits/stdc++.h>
#include "User.h"
#include "Admin.h"
#include "Hotel.h"
#include "hotel_manager.h"
#include "delivery.h"

using namespace std;

void displayMainMenu()
{
    cout << R"(

        █████   ███  ██████      ███████  ██████   ██████  ██████  ███████ 
       ██   ██ ██ ██      ██     ██      ██    ██ ██    ██ ██   ██ ██      
       ███████        █████      █████   ██    ██ ██    ██ ██   ██ ███████ 
       ██   ██            ██     ██      ██    ██ ██    ██ ██   ██      ██ 
       ██   ██       ██████      ██       ██████   ██████  ██████  ███████ 
                                                                    
                                                                    

        [1] Admin Login
        [2] User Login
        [3] Hotel Manager 
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

namespace main_funcs
{
    // Function to execute option 1
    void Admin()
    {
        // cout << "Executing Option 1..." << endl;
        cout << "\t\t\t Welcome to Admin Login" << endl;
        cout << "\t\t\t Enter Username: ";
        string username;
        global_funcs::input_flush();
        cin >> username;
        cout << "\t\t\t Enter Password: ";
        string password;
        global_funcs::input_flush();
        cin >> password;

        if (admin_funcs::login(username, password))
        {
            cout << "\t\t\t Login Successful!" << endl;
            cout << "\t\t\t Welcome " << username << "!" << endl;
            int choice = -1;
            do
            {
                cout << "\t\t\t 1. Add Hotel" << endl;
                cout << "\t\t\t 2. Remove Hotel" << endl;
                cout << "\t\t\t 3. View Hotels" << endl;
                cout << "\t\t\t 4. Add Users" << endl;
                cout << "\t\t\t 5. Remove Users" << endl;
                cout << "\t\t\t 6. View Users" << endl;
                cout << "\t\t\t 7. Add Items" << endl;
                cout << "\t\t\t 8. Remove Items" << endl;
                cout << "\t\t\t 9. View Items" << endl;
                cout << "\t\t\t 10. Add Manager" << endl;
                cout << "\t\t\t 11. Remove Manager" << endl;
                cout << "\t\t\t 12. View Managers" << endl;
                cout << "\t\t\t 13. Exit" << endl;
                cout << "\t\t\t Enter your choice: ";
                // int choice;
                global_funcs::get_input(choice);
                switch (choice)
                {
                case 1:
                    cout << "executing add hotel..." << endl;
                    Admin::add_hotel();
                    break;
                case 2:
                    cout << "executing remove hotel..." << endl;
                    Admin::remove_hotel();
                    break;
                case 3:
                    cout << "executing view hotels..." << endl;
                    Admin::view_hotels();
                    break;
                case 4:
                    cout << "executing add user..." << endl;
                    Admin::add_user();
                    break;
                case 5:
                    cout << "executing remove user..." << endl;
                    Admin::remove_user();
                    break;
                case 6:
                    cout << "executing view users..." << endl;
                    Admin::view_users();
                    break;
                case 7:
                    cout << "executing add item..." << endl;
                    Admin::add_item();
                    break;
                case 8:
                    cout << "executing remove item..." << endl;
                    Admin::remove_item();
                    break;
                case 9:
                    cout << "executing view items..." << endl;
                    Admin::view_items();
                    break;
                case 10:
                    cout << "executing add manager..." << endl;
                    Admin::add_manager();
                    break;
                case 11:
                    cout << "executing remove manager..." << endl;
                    Admin::remove_manager();
                    break;
                case 12:
                    cout << "executing view managers..." << endl;
                    Admin::view_managers();
                    break;
                case 13:
                    cout << "executing exit..." << endl;
                    break;        
                default:
                    cout << "Invalid choice!" << endl;
                }
            } while (choice != 13);
        }
        else
        {
            cout << "\t\t\t Login Failed!" << endl;
        }
        // cout << "Option 1 executed!" << endl << endl;
    }

    // Function to execute option 2
    void User()
    {
        cout << "\t\t\t Welcome to User Login" << endl;
        cout << "\t\t\t 1. Login" << endl;
        cout << "\t\t\t 2. Register" << endl;
        cout << "\t\t\t 3. Forgot Password" << endl;
        cout << "\t\t\t 4. Exit" << endl;
        cout << "\t\t\t Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
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
                )"
                 << endl;
            break;
        default:
            // system("cls");
            cout << "Invalid choice. Please try again." << endl
                 << endl;
            break;
        }
    }

    // Function to execute option 3
    void Hotel()
    {
        cout << "Executing Option 3..." << endl;
        // Your logic for Option 3 goes here

        Hotel_Manager::manager_menu();
        cout << "Option 3 executed!" << endl
             << endl;
    }

    void Delivery()
    {
        cout << "Executing Option 4..." << endl;
        DeliveryApp deliveryApp;

        cout << "\nDelivery Application\n";
        cout << "---------------------";

        while (true)
        {
            cout << deliveryApp;

            int choice = getDeliveryChoice();

            if (choice == -1)
            {
                break;
            }
            else if (choice == 0)
            {
                deliveryApp.displayDeliveryQueue();
                int deliveredChoice;
                cout << "\nEnter the item number that has been delivered (0 to continue): ";
                // cin >> deliveredChoice;
                global_funcs::get_input(deliveredChoice);
                deliveryApp.markItemDelivered(deliveredChoice);
            }
            else
            {
                deliveryApp.addItemToQueue(choice);
            }
        }

        deliveryApp.saveItemsToCSV();
        deliveryApp.saveDeliveryQueueToCSV();

        cout << "--------------------------------------------------------\n";
        cout << "THANK YOU FOR USING THE APP";
        // cout << "Option 4 executed!" << endl
        //      << endl;
    }
}

int main()
{
    int choice;
    bool exit = false;

    while (!exit)
    {
        displayMainMenu();
        // if(!(cin >> choice)) {
        //     cout << "Invalid choice. Please try again." << endl << endl;
        //     cin.clear();
        //     cin.ignore(10000, '\n');
        //     continue;
        // }
        // cin >> choice;
        global_funcs::get_input(choice, "Enter your choice: ");

        switch (choice)
        {
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
            cout << "Invalid choice. Please try again." << endl
                 << endl;
            break;
        }
    }

    return 0;
}
