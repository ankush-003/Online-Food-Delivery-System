#include <bits/stdc++.h>
#include "User.h"
#include "Hotel.h"

using namespace std;

int User::count = 0;

string User::user_db = "./Database/users.csv";

// inline void global_funcs::input_flush()
// {
//     cin.clear();
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');
// }

User::User(string userID, string password, string Address, string Phone): userID(userID), password(password), Address(Address), Phone(Phone)
{
    count++;
    cout << "\t\t\t Welcome " << userID << "!" << endl;
}

void User::select_hotel()
{
    cout << "Executing Hotel Selection..." << endl;
    ifstream hotels(hotel_db::hotels_db);
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
    ifstream items(hotel_db::items_db + selectedHotel + ".csv");
    if (!items.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }
    string line;
    stringstream ss;
    items >> line;
    string itemName, itemPrice, itemQuantity;
    cout << "\t\t\t" << "ID" << " " << "Item Name" << " " << "Price" << endl;
    int i = 1;
    while (items >> line)
    {
        ss << line;
        getline(ss, itemName, ',');
        getline(ss, itemPrice, ',');
        getline(ss, itemQuantity, ',');
        Item item(itemName, stoi(itemPrice), stoi(itemQuantity));
        cout << "\t\t\t " << i++ << ". " << item << endl;
        allItems.push_back(item);
        ss.clear();
    }
    // cout << "List Items executed!" << endl
}

void User::add_item()
{
    cout << "Executing Add Item..." << endl;
    string choice;
    do {
        cout << "\t\t\t Enter Item number to add: ";
        int opt = 0;
        // cin >> choice;
        global_funcs::get_input(opt);
        if (opt > allItems.size())
        {
            cout << "Invalid choice!" << endl;
            return;
        }
        allItems[opt - 1].quantity--;
        cart.push_back(allItems[opt - 1]);
        cout << allItems[opt - 1] << " added to cart!" << endl;
        cout << "\t\t\t Do you want to add more items? (y/n): ";
        global_funcs::input_flush();
        cin >> choice;
    } while (choice == "y" || choice == "Y");
    cout << "Items added to cart: " << endl;
    for (auto item : cart)
    {
        cout << "\t\t\t " << item << endl;
    }
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
    cout << "\t\t\t Item removed!" << endl;
}

void User::view_items()
{
    cout << "Executing View Items..." << endl;
    cout << "\t\t\t Items in cart: " << endl;
    for (auto item : cart)
    {
        cout << "\t\t\t " << item << endl;
    }
    // cout << "View Items executed!" << endl
    //      << endl;
}

void User::view_bill()
{
    cout << "Executing View Bill..." << endl;
    this -> total = 0;
    cout << "\t\t\t Items in cart: " << endl;
    for (auto item : cart)
    {
        cout << "\t\t\t " << item << endl;
        this -> total += item.price;
    }
    cout << "\t\t\t Total: " << this -> total << endl;
    // cout << "View Bill executed!" << endl
    //      << endl;
}

bool User::checkout() {
    cout << "Executing Checkout..." << endl;
    system("clear");
    cout << "\t\t\t Items in cart: " << endl;
    for (auto item : cart)
    {
        cout << "\t\t\t " << item << endl;
    }
    cout << "\t\t\t Total: " << this -> total << endl;
    cout << "\t\t\t Order Details: " << endl;
    cout << "\t\t\t Hotel Name: " << this -> selectedHotel << endl;
    cout << "\t\t\t Total: " << this -> total << endl;
    cout << "\t\t\t Address: " << this -> Address << endl;
    cout << "\t\t\t Phone: " << this -> Phone << endl;
    cout << "\t\t\t Do you want to confirm your order? (y/n): ";
    string choice;
    cin >> choice;
    if(choice == "y" || choice == "Y") {
        ofstream bill(this->userID + "_bill.txt"); 
        bill << "--- Bill ---" << endl;
        bill << "\t\t\t Order Details: " << endl;
        bill << "\t\t\t Hotel Name: " << this -> selectedHotel << endl;
        for (auto item : cart)
        {
            bill << "\t\t\t " << item << endl;
        }
        bill << "\t\t\t Total: " << this -> total << endl;
        bill << "\t\t\t Address: " << this -> Address << endl;
        bill << "\t\t\t Phone: " << this -> Phone << endl;
        bill << "--- Thank you for ordering! ---" << endl;
        bill.close();
        ofstream orders(hotel_db::orders_db, ios::app);
        orders << this -> userID << "," << this -> Address << "," << this -> Phone << "," << this -> selectedHotel << "," << this -> total << endl;
        orders.close();
        cout << "\t\t\t Order placed successfully!" << endl;
    } else {
        cout << "\t\t\t Order cancelled!" << endl;
        return false;
    }
    cout << "\t\t\t Checkout successful!" << endl;
    return true;
    // cout << "Checkout executed!" << endl
    //      << endl;
}

// void User::get_choice()

ostream &operator<<(ostream &os, User &user)
{
    os << "\t\t\t User ID: " << user.userID << endl;
    // os << "\t\t\t Password: " << user.password << endl;
    os << "\t\t\t Address: " << user.Address << endl;
    os << "\t\t\t Phone: " << user.Phone << endl;
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
    cout << "\t\t\t Executing User Login..." << endl;
    int count = 0;
    string userID, password, id, pass, address, phone, email;
    //////system("clear");
    cout << "\t\t\t Please Enter the username and password" << endl;
    cout << "\t\t\t Username: ";
    // cin >> userID;
    global_funcs::get_input(userID);
    cout << "\t\t\t Password: ";
    // cin >> password;
    global_funcs::get_input(password);
    ifstream input(User::user_db);
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
        getline(ss, address, ',');
        getline(ss, phone, ',');
        ss.clear();
        // cout << line << endl;
        // cout << id << " " << pass << endl;
        // cout << line << endl;
        if (userID == id && password == pass)
        {
            cout << "\t\t\t Login Successful!" << endl;
            User::count++;
            count++;
            User user(userID, password, address, phone);
            user.select_hotel();
            user.list_items();
            cout << "\t\t\t OPTIONS: " << endl;
            int choice;
            bool order_confirmed = false;
            while (!order_confirmed)
            {
                cout << "\t\t\t 1. Add Item" << endl;
                cout << "\t\t\t 2. Remove Item" << endl;
                cout << "\t\t\t 3. View Items" << endl;
                cout << "\t\t\t 4. View Bill" << endl;
                cout << "\t\t\t 5. Exit" << endl;
                cout << "\t\t\t Enter your choice: ";
                global_funcs::get_input(choice);
                string confirm;
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
                    cout << "\t\t\t Do you want to confirm the order? (y/n): ";
                
                    cin >> confirm;
                    if (confirm == "y" || confirm == "Y")
                    {
                        order_confirmed= user.checkout();
                    }
                    break;
                case 5:
                    cout << "Exiting..." << endl;
                    return;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
                }
                //////system("clear");
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
    string userID, password, address, phone;
    cout << "\t\t\t Enter username: ";
    global_funcs::get_input(userID);
    cout << "\t\t\t Enter password: ";
    global_funcs::get_input(password);
    cout << "\t\t\t Enter address: ";
    // global_funcs::get_input(address);
    // cin.clear();
    // cin.ignore(1000,'\n');
    global_funcs::input_flush();
    getline(cin, address);
    cout << "\t\t\t Enter phone: ";
    // cin.clear();
    // cin.ignore(1000,'\n');
    global_funcs::get_input(phone);
    ofstream output(User::user_db, ios::app);
    if(!output.is_open()){
        cout << "File not found!" << endl;
        return;
    }
    output << userID << "," << password << "," << address << "," << phone << "\n";
    output.close();
    cout << "\t\t\t User Registered Successfully!" << endl;
    cout << "\t\t\t Please login to continue!" << endl;
    system("clear");
    // cout << "User Registration executed!" << endl
}

void user_funcs::forgot()
{
    cout << "\t\t\t Executing User Forgot Password..." << endl;
    system("clear");
    int choice;
    cout << "\t\t\t 1. Search your id by username" << endl;
    cout << "\t\t\t 2. Go Back to Main Menu" << endl;
    cout << "\t\t\t Enter Your Choice: ";
    global_funcs::get_input(choice);
    string uname, upass, uaddress, uphone;
    string sname;
    string line;
    stringstream ss;
    ifstream database(User::user_db);
    if(!database.is_open()) {
        cout << "File Not Found!" << endl;
        return;
    }
    bool found = false;
    switch (choice)
    {
    case 1:
        cout << "\t\t\t Enter username: ";
        global_funcs::input_flush();
        global_funcs::get_input(sname);
        cout << "\t\t\t Searching for: " << sname << endl;
        database >> line;
        // cout << line;
        while(database >> line) {
            ss << line;
            getline(ss,uname,',');
            getline(ss, upass, ',');
            getline(ss, uaddress, ',');
            getline(ss, uphone, ',');
            // cout << uname << " " << upass << " " << " " << uaddress << " " << uphone << endl;
            ss.clear();
            if(uname == sname) {
                cout << "\t\t\t Account found!" << endl;
                fstream msg("msg.txt", ios::out);
                msg << "Your password is: " << upass << endl;
                msg.close();
                found = true;
            }
        }
        if(!found) {
            cout << "\t\t\t Invalid Username!" << endl;
        }
        break;
    
    case 2:
        cout << "\t\t\t Going back to Main Menu!" << endl;
        break; 
    default:
        cout << "\t\t\t Invalid Choice, Going Back!" << endl;
        break;
    }
    database.close();
    // cout << "User Forgot Password executed!" << endl
}
