#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cstring>
#include "hotel_manager.h"
#include "User.h"

Menu_Item::Menu_Item(const string &item_name, double item_price) : name(item_name), price(item_price) {}

Hotel_Manager::Hotel_Manager(const string &name, const string &hname) : manager_name(name), hotel_name(hname) {}

void Hotel_Manager::manager_menu()
{
    char name[100];
    string password;
    char hname[100];

    string manager_name_infile, manager_password_infile;

    int choice;

    do
    {
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "Enter your choice:" << endl;
        cin >> choice;

        fstream manager_database;

        try
        {
            switch (choice)
            {
            case 1:
                cout << "Please enter your username:" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cin.getline(name, 100);
                cout << "Please enter a password:" << endl;
                cin >> password;
                cout << "Please enter your hotel name:" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cin.getline(hname, 100);
                manager_database.open(manager_database_file, ios::app);
                if (manager_database.is_open())
                {
                    manager_database << name << "," << password << "," << hname << "\n";
                    manager_database.close();
                    cout << "You have successfully registered!\n";
                }
                else
                {
                    cout << "Failed to open the manager database file.\n";
                }
                break;

            case 2:
                cout << "Please enter your name:" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cin.getline(name, 100);
                cout << "Please enter a password:" << endl;
                cin >> password;

                manager_database.open(manager_database_file);
                if (manager_database.is_open())
                {
                    string line;
                    bool registered = false;
                    while (getline(manager_database, line))
                    {
                        stringstream ss(line);
                        getline(ss, manager_name_infile, ',');
                        getline(ss, manager_password_infile, ',');
                        ss.getline(hname, 100, ',');

                        if (name == manager_name_infile && password == manager_password_infile)
                        {
                            registered = true;
                            cout << "Login Successful!!!" << endl;
                            Hotel_Manager manager(name, hname);
                            // manager.add_item_to_menu("Pizza", 9.6);
                            // manager.add_item_to_menu("Burger", 6.9);
                            // manager.add_item_to_menu("Pasta", 20.0);
                            // manager.delete_item_from_menu("Burger");

                            int manager_choice;
                            char item_name[100];
                            float item_price;

                            // int manager_continue = -1;

                            int manager_continue = -1;
                            do
                            {
                                cout << "What do you want to do?" << endl;

                                cout << "1.Add item to the menu" << endl;
                                cout << "2.Remove item from the menu" << endl;
                                cout << "3.Display the menu" << endl;

                                cout << "Enter your choice:" << endl;
                                cin >> manager_choice;

                                fstream menu;


                                switch (manager_choice)
                                {
                                case 1:

                                    cout << "Enter the name of the item you want to add:" << endl;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cin.getline(item_name, 100);
                                    cout << "Enter the price of the item that you just enetered:" << endl;
                                    cin >> item_price;
                                    manager.add_item_to_menu(item_name, item_price);
                                    break;

                                case 2:
                                    cout << "Enter the name of the item you want to delete:" << endl;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cin.getline(item_name, 100);
                                    manager.delete_item_from_menu(item_name);
                                    break;

                                case 3:
                                    cout << "Menu of " << std::string(hname) << endl;

                                    menu.open(std::string("./Database/menu_") + hname + ".csv");
                                    if (menu.is_open())
                                    {
                                        string line;
                                        while (getline(menu, line))
                                        {
                                            stringstream ss(line);
                                            char item_name[100];
                                            double item_price;
                                            ss.get(item_name, 100, ',');
                                            ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');

                                            ss >> item_price;
                                            cout << "Item: " << item_name << " | Price: " << item_price << endl;
                                        }
                                        menu.close();
                                    }
                                    else
                                    {
                                        cout << "Failed to open the menu file." << endl;
                                        
                                    }
                                    break;  //

                                default:
                                    cout << "Invalid choice" << endl;
                                    break;
                                }

                                cout << "Do you want to continue? (Y(1)/N(0)): ";
                                cin.clear();
                                cin.ignore(1000, '\n');
                                global_funcs::get_input(manager_continue);
                                // cin >> manager_choice;
                                // cout << manager_continue << endl;
                                if(!manager_continue) {
                                    break;
                                }
                            } while (1);
                        }
                    }
                    manager_database.close();

                    if (!registered)
                    {
                        cout << "Sorry, you are not registered. Please register yourself to continue" << endl;
                    }
                }
                else
                {
                    throw std::runtime_error("Failed to open the manager database file.");
                }
                break;

            case 3:
                cout << "You exited" << endl;
                choice = 0;
                break;

            default:
                cout << "Invalid choice" << endl;
                break;
            }
        }

        catch (const std::exception &ex)
        {
            cout << "An error occurred: " << ex.what() << endl;
        }
    } while (choice);
}

void Hotel_Manager::add_item_to_menu(const string &item_name, double item_price)
{
    ofstream menufile("./Database/menu_" + hotel_name + ".csv", ios::app); // app is append mode
    if (menufile.is_open())
    {
        menufile << item_name << "," << item_price << "\n";
        menufile.close();
        cout << "Item added to the menu successfully.\n";
    }
    else
    {
        cout << "Failed to open the menu database file.\n";
    }
}

void Hotel_Manager::delete_item_from_menu(const string &item_name)
{
    // Read the menu database file into memory
    ifstream menufile("./Database/menu_" + hotel_name + ".csv");
    if (menufile.is_open())
    {
        vector<Menu_Item> Menu_Items;
        string line;
        while (getline(menufile, line))
        {
            string item_name_in_file = line.substr(0, line.find(','));
            double item_price_in_file = stod(line.substr(line.find(',') + 1));
            Menu_Items.push_back(Menu_Item(item_name_in_file, item_price_in_file));
        }
        menufile.close();

        // Find and remove the item from the Menu_Items vector
        bool found = false;

        auto it = std::find_if(Menu_Items.begin(), Menu_Items.end(), [&](const Menu_Item &item)
                               { return item.name == item_name; });
        if (it != Menu_Items.end())
        {
            Menu_Items.erase(it);

            // Rewrite the menu database file with updated Menu_Items
            ofstream updated_menu_file("./Database/menu_" + hotel_name + ".csv");
            if (updated_menu_file.is_open())
            {
                for (const auto &item : Menu_Items)
                {
                    updated_menu_file << item.name << "," << item.price << "\n";
                }
                updated_menu_file.close();
                cout << "Item deleted from the menu successfully.\n";
            }
            else
            {
                cout << "failed to open database file.\n";
            }
        }
        else
        {
            cout << "Item not there in menu.\n";
        }
    }
    else
    {
        cout << "Failed to open the menu database file.\n";
    }
}

string Hotel_Manager::menu_database_file = "./Database/menu_abc.csv";
string Hotel_Manager::manager_database_file = "./Database/managers.csv";
