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
    file << name << "," << address << "," << phone << "," << email << endl;
    file.close();
    cout << "\t\t\t Hotel added successfully!" << endl;
}