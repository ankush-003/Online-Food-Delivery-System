#include <bits/stdc++.h>
#include "User.h"
#include "Hotel.h"

using namespace std;

// class User {
//     static int count;
//     string password;
//     public:
//     string userID;
//     string selectedHotel;
//     vector<Item> allItems;
//     vector<Item> cart;
//     User(string userID, string password): userID(userID), password(password) {
//         count++;
//         cout << "\t\t\t Welcome " << userID << "!" << endl;
//     }
//     void select_hotel() {
//         cout << "Executing Hotel Selection..." << endl;
//         ifstream hotels("./Database/hotels.csv");
//         if(!hotels.is_open()) {
//             cout << "File not found!" << endl;
//             return;
//         }
//         string line;
//         stringstream ss;
//         getline(hotels, line, ',');
//         string hotelName, hotelpwd, hotelAddress, hotelPhone, hotelEmail;
//         cout << "\t\t\t Hotels Available: " << endl;
//         vector<string> hotelNames;
//         int i = 1;
//         while(getline(hotels, line, ',')) {
//             ss << line;
//             getline(ss, hotelName, ',');
//             getline(ss, hotelpwd, ',');
//             getline(ss, hotelAddress, ',');
//             getline(ss, hotelPhone, ',');
//             getline(ss, hotelEmail, ',');
//             cout << "\t\t\t " << ++i << ". " << hotelName << endl;
//             hotelNames.push_back(hotelName);
//             ss.clear();
//         }
//         cout << "\t\t\t Enter your choice: ";
//         int choice;
//         cin >> choice;
//         selectedHotel = hotelNames[choice - 1];
//         cout << "\t\t\t You have selected " << selectedHotel << endl;
//         cout << "Hotel Selection executed!" << endl << endl;
//     }

//     void list_items() {
//         cout << "Executing List Items..." << endl;
//         cout << "\t\t\t Items Available: " << endl;
//         ifstream items("./Database/" + selectedHotel + ".csv");
//         if(!items.is_open()) {
//             cout << "File not found!" << endl;
//             return;
//         }
//         string line;
//         stringstream ss;
//         getline(items, line, ',');
//         string itemName, itemPrice;
//         int i = 1;
//         while(getline(items, line, ',')) {
//             ss << line;
//             getline(ss, itemName, ',');
//             getline(ss, itemPrice, ',');
//             cout << "\t\t\t " << ++i << ". " << itemName << " " << itemPrice << endl;
//             Item item(itemName, stoi(itemPrice));
//             allItems.push_back(item);
//             ss.clear();
//         }
//         cout << "List Items executed!" << endl << endl;
//     }

//     void add_item(Item item) {
//         cout << "Executing Add Item..." << endl;
//         cout << "\t\t\t Enter Item number to add: ";
//         int choice;
//         cin >> choice;
//         cart.push_back(allItems[choice - 1]);
//         cout << allItems[choice - 1]<< " added to cart!" << endl;
//         // cout << "Item added!" << endl << endl;
//     }
//     void remove_item(Item) {
//         cout << "Executing Remove Item..." << endl;
//         for(int i = 0; i < cart.size(); i++) {
//             cout << "\t\t\t " << i + 1 << ". " << cart[i] << endl;
//         }

//         cout << "\t\t\t Enter Item number to remove: ";
//         int choice;
//         cin >> choice;
//         cart.erase(cart.begin() + choice - 1);
//         cout << "Item removed!" << endl << endl;
//     }
//     void view_items() {
//         cout << "Executing View Items..." << endl;
//         cout << "\t\t\t Items in cart: " << endl;
//         for(auto item: cart) {
//             cout << "\t\t\t " << item << endl;
//         }
//         cout << "View Items executed!" << endl << endl;
//     }
//     void view_bill() {
//         cout << "Executing View Bill..." << endl;
//         int total = 0;
//         cout << "\t\t\t Items in cart: " << endl;
//         for(auto item: cart) {
//             cout << "\t\t\t " << item << endl;
//             total += item.getPrice();
//         }
//         cout << "\t\t\t Total: " << total << endl;
//         cout << "View Bill executed!" << endl << endl;
//     }
//     friend ostream& operator<<(ostream&, User&);
// };

int User::count = 0;

User::User(string userID, string password) : userID(userID), password(password)
{
    // count++;
    cout << "\t\t\t Welcome " << userID << "!" << endl;
}

void User::select_hotel()
{
    cout << "Executing Hotel Selection..." << endl;
    ifstream hotels("./Database/hotels.csv");
    if (!hotels.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }
    string line;
    stringstream ss;
    hotels >> line;
    string hotelName, hotelpwd, hotelAddress, hotelPhone, hotelEmail;
    cout << "\t\t\t Hotels Available: " << endl;
    vector<string> hotelNames;
    int i = 1;
    cout << "\t\t\t" << "Hotel Name" << endl;
    while (hotels >> line)
    {
        ss << line;
        getline(ss, hotelName, ',');
        getline(ss, hotelpwd, ',');
        getline(ss, hotelAddress, ',');
        getline(ss, hotelPhone, ',');
        getline(ss, hotelEmail, ',');
        // cout << line << endl;
        cout << "\t\t\t " << i++ << ". " << hotelName << endl;
        hotelNames.push_back(hotelName);
        ss.clear();
    }
    cout << "\t\t\t Enter your choice: ";
    int choice;
    cin >> choice;
    if (choice > hotelNames.size())
    {
        cout << "Invalid choice!" << endl;
        return;
    }
    selectedHotel = hotelNames[choice - 1];
    cout << "\t\t\t You have selected " << selectedHotel << endl;
    cout << "Hotel Selection executed!" << endl
         << endl;
}

void User::list_items()
{
    cout << "Executing List Items..." << endl;
    cout << "\t\t\t Items Available: " << endl;
    ifstream items("./Database/menu_" + selectedHotel + ".csv");
    if (!items.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }
    string line;
    stringstream ss;
    items >> line;
    string itemName, itemPrice;
    cout << "\t\t\t" << "ID" << " " << "Item Name" << " " << "Price" << endl;
    int i = 1;
    while (items >> line)
    {
        ss << line;
        getline(ss, itemName, ',');
        getline(ss, itemPrice, ',');
        cout << "\t\t\t " << i++ << ". " << itemName << " " << itemPrice << endl;
        Item item(itemName, stoi(itemPrice));
        allItems.push_back(item);
        ss.clear();
    }
    cout << "List Items executed!" << endl
         << endl;
}

void User::add_item()
{
    cout << "Executing Add Item..." << endl;
    cout << "\t\t\t Enter Item number to add: ";
    int choice;
    cin >> choice;
    if (choice > allItems.size())
    {
        cout << "Invalid choice!" << endl;
        return;
    }
    cart.push_back(allItems[choice - 1]);
    cout << allItems[choice - 1] << " added to cart!" << endl;
    // cout << "Item added!" << endl << endl;
}

void User::remove_item()
{
    cout << "Executing Remove Item..." << endl;
    for (int i = 0; i < cart.size(); i++)
    {
        cout << "\t\t\t " << i + 1 << ". " << cart[i] << endl;
    }

    cout << "\t\t\t Enter Item number to remove: ";
    int choice;
    cin >> choice;
    if (choice > cart.size())
    {
        cout << "Invalid choice!" << endl;
        return;
    }
    cart.erase(cart.begin() + choice - 1);
    cout << "Item removed!" << endl
         << endl;
}

void User::view_items()
{
    cout << "Executing View Items..." << endl;
    cout << "\t\t\t Items in cart: " << endl;
    for (auto item : cart)
    {
        cout << "\t\t\t " << item << endl;
    }
    cout << "View Items executed!" << endl
         << endl;
}

void User::view_bill()
{
    cout << "Executing View Bill..." << endl;
    int total = 0;
    cout << "\t\t\t Items in cart: " << endl;
    for (auto item : cart)
    {
        cout << "\t\t\t " << item << endl;
        total += item.getPrice();
    }
    cout << "\t\t\t Total: " << total << endl;
    cout << "View Bill executed!" << endl
         << endl;
}

ostream &operator<<(ostream &os, User &user)
{
    os << "\t\t\t User ID: " << user.userID << endl;
    os << "\t\t\t Password: " << user.password << endl;
    os << "\t\t\t Selected Hotel: " << user.selectedHotel << endl;
    os << "\t\t\t Cart: " << endl;
    for (auto item : user.cart)
    {
        os << "\t\t\t " << item << endl;
    }
    return os;
}

void user_funcs::login()
{
    cout << "Executing User Login..." << endl;
    int count;
    string userID, password, id, pass;
    //////system("clear");
    cout << "\t\t\t Please Enter the username and password" << endl;
    cout << "\t\t\t Username: ";
    cin >> userID;
    cout << "\t\t\t Password: ";
    cin >> password;
    ifstream input("./Database/users.csv");
    if (!input.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }
    string line;
    stringstream ss;
    input >> line;
    while (input >> line)
    {
        ss << line;
        getline(ss, id, ',');
        getline(ss, pass, ',');
        ss.clear();
        // cout << line << endl;
        // cout << id << " " << pass << endl;
        // cout << line << endl;
        if (userID == id && password == pass)
        {
            cout << "\t\t\t Login Successful!" << endl;
            User::count++;
            count++;
            User user(userID, password);
            user.select_hotel();
            user.list_items();
            int choice;
            while (true)
            {
                cout << "\t\t\t 1. Add Item" << endl;
                cout << "\t\t\t 2. Remove Item" << endl;
                cout << "\t\t\t 3. View Items" << endl;
                cout << "\t\t\t 4. View Bill" << endl;
                cout << "\t\t\t 5. Exit" << endl;
                cout << "\t\t\t Enter your choice: ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                    user.add_item();
                    break;
                case 2:
                    user.remove_item();
                    break;
                case 3:
                    user.view_items();
                    break;
                case 4:
                    user.view_bill();
                    break;
                case 5:
                    cout << "Exiting..." << endl;
                    return;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
                }
                //////system("clear");
                break;
            }
        }
    }
    input.close();
    if (count == 0)
    {
        cout << "\t\t\t Invalid Username or Password!" << endl;
        cout << "\t\t\t Please try again!" << endl;
        // ////system("pause");
        // ////system("cls");
        return;
    }

    cout << "User Login executed!" << endl
         << endl;
}

void user_funcs::registerUser()
{
    cout << "Executing User Registration..." << endl;
    // Your logic for User Registration goes here
    cout << "User Registration executed!" << endl
         << endl;
}

void user_funcs::forgot()
{
    cout << "Executing User Forgot Password..." << endl;
    // Your logic for User Forgot Password goes here
    cout << "User Forgot Password executed!" << endl
         << endl;
}
