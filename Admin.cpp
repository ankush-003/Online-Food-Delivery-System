#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Hotel.h"
#include "User.h"
#include "Admin.h"
using namespace std;

bool admin_funcs::login(string username, string password) {
    ifstream file(admin_funcs::admin_db);
    string line;
    stringstream ss;
    string id, pass, role;
    file >> line;
    while(file >> line) {
        ss << line;
        getline(ss, id, ',');
        getline(ss, pass, ',');
        getline(ss, role, ',');
        ss.clear();
        if(id == username && pass == password) {
            return true;
        }
        cout << "\t\t\t Welcome " << username << "!" << endl;
        // cout << id << " " << pass << " " << role << endl;
    }
    return false;
}

Admin::Admin(string username, string password, string role) {
    this->adminID = username;
    this->password = password;
    this->role = role;
}

bool Admin::search_hotel(string name) {
    ifstream file(hotel_db::hotels_db);
    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return false;
    }
    string line;
    stringstream ss;
    string n, address, phone, email;
    file >> line;
    while(file >> line) {
        ss << line;
        getline(ss, n, ',');
        getline(ss, address, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        ss.clear();
        if(n == name) {
            return true;
        }
    }
    return false;
}

void Admin::add_hotel() {
    string name, address, phone, email;
    cout << "Enter hotel name: ";
    global_funcs::input_flush();
    getline(cin, name);
    cout << "Enter hotel address: ";
    // global_funcs::input_flush();
    getline(cin, address);
    cout << "Enter hotel phone: ";
    getline(cin, phone);
    cout << "Enter hotel email: ";
    // global_funcs::input_flush();
    getline(cin, email);

    ofstream file(hotel_db::hotels_db, ios::app);
    if (!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }
    bool found = search_hotel(name);
    if(found) {
        cout << "Hotel already exists!" << endl;
        return;
    }
    file << name << "," << address << "," << phone << "," << email << endl;
    file.close();
    cout << "\t\t\t Hotel added successfully!" << endl;
}


void Admin::remove_hotel() {
    string name;
    cout << "Enter hotel name: ";
    global_funcs::input_flush();
    getline(cin, name);
    auto update = [](string name) {
        ifstream file(hotel_db::hotels_db);
        ofstream temp("temp.csv");
        if(!file.is_open()) {
            cout << "Error opening file!" << endl;
            return false;
        }
        bool found = false;
        string line;
        stringstream ss;
        string n, address, phone, email;
        file >> line;
        temp << line << endl;
        while(file >> line) {
            ss << line;
            getline(ss, n, ',');
            getline(ss, address, ',');
            getline(ss, phone, ',');
            getline(ss, email, ',');
            ss.clear();
            if(n != name) {
                temp << line << endl;
            } else {
                found = true;
            }
        }
        file.close();
        temp.close();
        if(!found) {
            return false;
        }
        string fname = hotel_db::hotels_db;
        remove(fname.c_str());
        rename("temp.csv", fname.c_str());
        return true;
    };
    if(!update(name)) {
        cout << "\t\t\t Hotel not found!" << endl;
        return;
    }
    cout << "\t\t\t Hotel removed successfully!" << endl;
}

bool Admin::search_user(string username) {
    ifstream file(Admin::user_db);
    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return false;
    }
    string line;
    stringstream ss;
    string n, password, address, phone;
    file >> line;
    while(file >> line) {
        ss << line;
        getline(ss, n, ',');
        getline(ss, password, ',');
        getline(ss, address, ',');
        getline(ss, phone, ',');
        ss.clear();
        if(n == username) {
            return true;
        }
    }
    return false;
}

void Admin::add_user() {
    string name, password, address, phone;
    cout << "Enter user name: ";
    global_funcs::input_flush();
    getline(cin, name);
    cout << "Enter user password: ";
    getline(cin, password);
    cout << "Enter user address: ";
    global_funcs::input_flush();
    getline(cin, address);
    cout << "Enter user phone: ";
    getline(cin, phone);
    
    ofstream file(Admin::user_db, ios::app);
    if (!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }
    bool found = search_user(name);
    if(found) {
        cout << "User already exists!" << endl;
        return;
    }
    file << name << "," << password << "," << address << "," << phone << endl;
    file.close();
    cout << "\t\t\t User added successfully!" << endl;
    cout << "\t\t\t User ID: " << name << endl;
}

void Admin::remove_user() {
    string name;
    cout << "Enter user name: ";
    global_funcs::input_flush();
    getline(cin, name);
    auto update = [](string name) {
        ifstream file(Admin::user_db);
        ofstream temp("temp.csv");
        if(!file.is_open()) {
            cout << "Error opening file!" << endl;
            return false;
        }
        bool found = false;
        string line;
        stringstream ss;
        string n, password, address, phone;
        file >> line;
        temp << line << endl;
        while(file >> line) {
            ss << line;
            getline(ss, n, ',');
            getline(ss, password, ',');
            getline(ss, address, ',');
            getline(ss, phone, ',');
            ss.clear();
            if(n != name) {
                temp << line << endl;
            } else {
                found = true;
            }
        }
        file.close();
        temp.close();
        if(!found) {
            return false;
        }
        string fname = Admin::user_db;
        remove(fname.c_str());
        rename("temp.csv", fname.c_str());
        return true;
    };
    if(!update(name)) {
        cout << "\t\t\t User not found!" << endl;
        return;
    }

    cout << "\t\t\t User removed successfully!" << endl;
}

void Admin::add_item() {
    cout << "Enter Hotel name: ";
    string hotel_name;
    global_funcs::input_flush();
    getline(cin, hotel_name);
    bool found = false;
    auto search = [](string hotel_name) {
        ifstream file(hotel_db::hotels_db);
        string line;
        stringstream ss;
        string name, address, phone, email;
        file >> line;
        while(file >> line) {
            ss << line;
            getline(ss, name, ',');
            getline(ss, address, ',');
            getline(ss, phone, ',');
            getline(ss, email, ',');
            ss.clear();
            if(name == hotel_name) {
                return true;
            }
        }
        return false;
    };
    found = search(hotel_name);
    if(!found) {
        cout << "\t\t\t Hotel not found!" << endl;
        return;
    }
    string fname = hotel_db::items_db + hotel_name + ".csv";
    vector<Item> items;
    ifstream file(fname);
    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    string line;
    stringstream ss;
    string name, price, quantity;
    file >> line;
    while(file >> line) {
        ss << line;
        getline(ss, name, ',');
        getline(ss, price, ',');
        getline(ss, quantity, ',');
        ss.clear();
        Item item(name, stoi(price), stoi(quantity));
        items.push_back(item);
    }
    file.close();
    cout << "\t\t\t Available items: " << endl;
    for(int i = 0; i < items.size(); i++) {
        cout << "\t\t\t " << i + 1 << ". " << items[i] << endl;
    }
    cout << "\t\t\t Enter item name: ";
    string item_name;
    global_funcs::input_flush();
    getline(cin, item_name);
    auto search_item = [&items](string item_name) {
        for(int i = 0; i < items.size(); i++) {
            if(items[i].name == item_name) {
                return true;
            }
        }
        return false;
    };
    if(search_item(item_name)) {
        cout << "\t\t\t Item already exists!" << endl;
        return;
    }
    cout << "\t\t\t Enter item price: ";
    string item_price;
    getline(cin, item_price);
    cout << "\t\t\t Enter item quantity: ";
    string item_quantity;
    getline(cin, item_quantity);
    ofstream file2(fname, ios::app);
    if(!file2.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    file2 << item_name << "," << item_price << "," << item_quantity << endl;
    file2.close();
    cout << "\t\t\t Item added successfully!" << endl;
}

void Admin::remove_item() {
    
    cout << "Enter Hotel name: ";
    string hotel_name;
    global_funcs::input_flush();
    getline(cin, hotel_name);
    bool found = false;
    found = search_hotel(hotel_name);
    if(!found) {
        cout << "\t\t\t Hotel not found!" << endl;
        return;
    }
    string fname = hotel_db::items_db + hotel_name + ".csv";
    vector<Item> items;
    ifstream file(fname);
    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    string line;
    stringstream ss;
    string name, price, quantity;
    file >> line;
    while(file >> line) {
        ss << line;
        getline(ss, name, ',');
        getline(ss, price, ',');
        getline(ss, quantity, ',');
        ss.clear();
        Item item(name, stoi(price), stoi(quantity));
        items.push_back(item);
    }
    file.close();
    cout << "\t\t\t Available items: " << endl;
    for(int i = 0; i < items.size(); i++) {
        cout << "\t\t\t " << i + 1 << ". " << items[i] << endl;
    }
    cout << "\t\t\t Enter item name: ";
    string item_name;
    global_funcs::input_flush();
    getline(cin, item_name);
    auto search_item = [&items](string item_name) {
        for(int i = 0; i < items.size(); i++) {
            if(items[i].name == item_name) {
                return true;
            }
        }
        return false;
    };
    if(!search_item(item_name)) {
        cout << "\t\t\t Item not found!" << endl;
        return;
    }
    auto update = [&items, &item_name](string fname) {
        ofstream temp("temp.csv");
        if(!temp.is_open()) {
            cout << "Error opening file!" << endl;
            return false;
        }
        bool found = false;
        string line;
        stringstream ss;
        string n, price, quantity;
        temp << "Name,Price,Quantity" << endl;
        for(int i = 0; i < items.size(); i++) {
            if(items[i].name != item_name) {
                temp << items[i].name << "," << items[i].price << "," << items[i].quantity << endl;
            } else {
                found = true;
            }
        }
        temp.close();
        if(!found) {
            return false;
        }
        string fname2 = hotel_db::items_db + fname + ".csv";
        remove(fname2.c_str());
        rename("temp.csv", fname2.c_str());
        return true;
    };
    if(update(hotel_name)) {
        cout << "\t\t\t Item removed successfully!" << endl;
    } else {
        cout << "\t\t\t Error removing item!" << endl;
    }

}

void Admin::view_users() {
    ifstream file(User::user_db);
    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    string line;
    stringstream ss;
    string username, password, name, phone, email;
    file >> line;
    cout << "\t\t\t----- Users -----" << endl;
    cout << "\t\t\t Username Phone Email" << endl;
    while(file >> line) {
        ss << line;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        ss.clear();
        cout << "\t\t\t " << username << " " << " " << phone << " " << email << endl;
    }
    cout << "\t\t\t----------" << endl;
    file.close();
}

void Admin::view_hotels() {
    ifstream file(hotel_db::hotels_db);
    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    string line;
    stringstream ss;
    string name, address, phone, email;
    file >> line;
    cout << "\t\t\t----- Hotels: -----" << endl;
    cout << "\t\t\t Hotel_name Address Phone Email" << endl;
    while(file >> line) {
        ss << line;
        getline(ss, name, ',');
        getline(ss, address, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        ss.clear();
        cout << "\t\t\t " << name << " " << address << " " << phone << " " << email << endl;
    }
    cout << "\t\t\t----------" << endl;
    file.close();
}

void Admin::view_items() {
    cout << "\t\t\t Enter Hotel name: ";
    string hotel_name;
    global_funcs::input_flush();
    getline(cin, hotel_name);
    bool found = false;
    found = search_hotel(hotel_name);
    if(!found) {
        cout << "\t\t\t Hotel not found!" << endl;
        return;
    }
    string fname = hotel_db::items_db + hotel_name + ".csv";
    ifstream file(fname);
    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    string line;
    stringstream ss;
    string name, price, quantity;
    file >> line;
    cout << "\t\t\t----- Items -----" << endl;
    cout << "\t\t\t Name Price Quantity" << endl;
    while(file >> line) {
        ss << line;
        getline(ss, name, ',');
        getline(ss, price, ',');
        getline(ss, quantity, ',');
        ss.clear();
        cout << "\t\t\t " << name << " " << price << " " << quantity << endl;
    }
    cout << "\t\t\t----------" << endl;
    file.close();
}

bool Admin::search_manager(string mname) {
    ifstream file("./Database/managers.csv");
    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return false;
    }
    string line;
    stringstream ss;
    string manager_name, password, hotel_name;
    // file >> line;
    while(file >> line) {
        ss << line;
        getline(ss, manager_name, ',');
        getline(ss, password, ',');
        getline(ss, hotel_name, ',');
        ss.clear();
        if(manager_name == mname) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void Admin::add_manager() {
    cout << "\t\t\t Enter Manager name: ";
    string manager_name;
    global_funcs::input_flush();
    getline(cin, manager_name);
    if(search_manager(manager_name)) {
        cout << "\t\t\t Manager already exists!" << endl;
        return;
    }
    cout << "\t\t\t Enter Manager password: ";
    string password;
    // global_funcs::input_flush();
    getline(cin, password);
    cout << "\t\t\t Enter Hotel name: ";
    string hotel_name;
    // global_funcs::input_flush();
    getline(cin, hotel_name);
    if(!search_hotel(hotel_name)) {
        cout << "\t\t\t Hotel not found!" << endl;
        return;
    }
    ofstream file("./Database/managers.csv", ios::app);
    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    file << manager_name << "," << password << "," << hotel_name << endl;
    file.close();
    cout << "\t\t\t Manager added successfully!" << endl;
}

void Admin::remove_manager() {
    cout << "\t\t\t Enter Manager name: ";
    string manager_name;
    global_funcs::input_flush();
    getline(cin, manager_name);
    if(!search_manager(manager_name)) {
        cout << "\t\t\t Manager not found!" << endl;
        return;
    }
    bool found = false;
    auto update = [&](string mname) {
        ifstream file("./Database/managers.csv");
        if(!file.is_open()) {
            cout << "Error opening file!" << endl;
            return false;
        }
        string line;
        stringstream ss;
        string manager_name, password, hotel_name;
        ofstream temp("temp.csv");
        if(!temp.is_open()) {
            cout << "Error opening file!" << endl;
            return false;
        }
        while(file >> line) {
            ss << line;
            getline(ss, manager_name, ',');
            getline(ss, password, ',');
            getline(ss, hotel_name, ',');
            ss.clear();
            if(manager_name != mname) {
                temp << manager_name << "," << password << "," << hotel_name << endl;
            } else {
                found = true;
            }
        }
        temp.close();
        if(!found) {
            return false;
        }
        remove("./Database/managers.csv");
        rename("temp.csv", "./Database/managers.csv");
        return true;
    };
    if(update(manager_name)) {
        cout << "\t\t\t Manager removed successfully!" << endl;
    } else {
        cout << "\t\t\t Error removing manager!" << endl;
    }
}

void Admin::view_managers() {
    ifstream file("./Database/managers.csv");
    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    string line;
    stringstream ss;
    string manager_name, password, hotel_name;
    file >> line;
    cout << "\t\t\t----- Managers: -----" << endl;
    cout << "\t\t\t Manager_name Password Hotel_name" << endl;
    while(file >> line) {
        ss << line;
        getline(ss, manager_name, ',');
        getline(ss, password, ',');
        getline(ss, hotel_name, ',');
        ss.clear();
        cout << "\t\t\t " << manager_name << " " << password << " " << hotel_name << endl;
    }
    cout << "\t\t\t----------" << endl;
    file.close();
}