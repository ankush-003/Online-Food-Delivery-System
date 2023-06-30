#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "hotel_manager.h"

Menu_Item::Menu_Item(const string &item_name, double item_price) : name(item_name), price(item_price) {}

Hotel_Manager::Hotel_Manager(const string &name, const string &hname) : manager_name(name), hotel_name(hname) {}

void Hotel_Manager::manager_menu()
{
    string name;
    string password;
    string hname;

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
        switch (choice)
        {
        case 1:
            cout << "Please enter your username:" << endl;
            cin >> name;
            cout << "Please enter a password:" << endl;
            cin >> password;
            cout << "Please enter your hotel name:" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            getline(cin, hname, '\n');
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
            cin >> name;
            cout << "Please enter a password:" << endl;
            cin >> password;

            manager_database.open(manager_database_file);
            if (manager_database.is_open())
            {
                string line;
                while (getline(manager_database, line))
                {
                    stringstream ss(line);
                    getline(ss, manager_name_infile, ',');
                    getline(ss, manager_password_infile, ',');
                    getline(ss, hname, ',');

                    if (name == manager_name_infile && password == manager_password_infile)
                    {
                        cout << "Login Successful!!!" << endl;
                        Hotel_Manager manager(name, hname);
                        // manager.add_item_to_menu("Pizza", 9.6);
                        // manager.add_item_to_menu("Burger", 6.9);
                        // manager.add_item_to_menu("Pasta", 20.0);
                        // manager.delete_item_from_menu("Burger");

                        int manager_choice;
                        string item_name;
                        float item_price;

                        string manager_continue;

                        do
                        {
                            cout << "What do you want to do?" << endl;

                            cout << "1.Add item to the menu" << endl;
                            cout << "2.Remove item from the menu" << endl;
                            cout << "3.Display the menu" << endl;

                            cout << "Enter your choice:" << endl;
                            cin >> manager_choice;

                            fstream menu;

                            string manager_continue;

                            switch (manager_choice)
                            {
                            case 1:

                                cout << "Enter the name of the item you want to add:" << endl;
                                cin >> item_name;
                                cout << "Enter the of the item that you just enetered:" << endl;
                                cin >> item_price;
                                manager.add_item_to_menu(item_name, item_price);
                                break;

                            case 2:
                                cout << "Enter the name of the item you want to delete:" << endl;
                                cin >> item_name;
                                manager.delete_item_from_menu(item_name);
                                break;

                            case 3:
                                cout << "Menu of " << hname << endl;

                                menu.open("menu_" + hname + ".csv");
                                if (menu.is_open())
                                {
                                    string line;
                                    while (getline(menu, line))
                                    {
                                        stringstream ss(line);
                                        string item_name;
                                        double item_price;
                                        getline(ss, item_name, ',');
                                        ss >> item_price;
                                        cout << "Item: " << item_name << " | Price: " << item_price << endl;
                                    }
                                    menu.close();
                                }
                                else
                                {
                                    cout << "Failed to open the menu file." << endl;
                                }
                                break;

                            default:
                                cout << "Invalid choice" << endl;
                                break;
                            }

                            cout << "Do you want to continue? (Y/N): ";
                            cin >> manager_continue;
                        } while (manager_continue == "Y" || manager_continue == "y");
                    }
                }
                manager_database.close();
            }
            break;

        case 3:
            cout << "You exited" << endl;
            choice = 0;
            break;

        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice);
}

void Hotel_Manager::add_item_to_menu(const string &item_name, double item_price)
{
    ofstream menufile("menu_" + hotel_name + ".csv", ios::app); // app is append mode
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
        ifstream menufile(menu_database_file);
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
            for (auto it = Menu_Items.begin(); it != Menu_Items.end(); ++it)
            {
                if (it->name == item_name)
                {
                    Menu_Items.erase(it);
                    found = true;
                    break;
                }
            }
            // Rewrite the menu database file with updated Menu_Items
            ofstream updated_menu_file(menu_database_file);
            if (updated_menu_file.is_open())
            {
                for (const auto &item : Menu_Items)
                {
                    updated_menu_file << item.name << "," << item.price << "\n";
                }
                updated_menu_file.close();
                if (found)
                    cout << "Item deleted from the menu successfully.\n";
                else
                    cout << "Item not found in the menu.\n";
            }
            else
            {
                cout << "Failed to open the menu database file.\n";
            }
        }
        else
        {
            cout << "Failed to open the menu database file.\n";
        }
}


string Hotel_Manager::menu_database_file = "menu_abc.csv";
string Hotel_Manager::manager_database_file = "managers.csv";



