#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Hotel.h"
#include "User.h"
using namespace std;
#ifndef ADMIN_H
#define ADMIN_H

class Admin: public User {
    string password;
    public:
    string adminID;
    string role;
    Admin(string, string, string);
    void add_hotel();
    void remove_hotel();
    void add_item();
    void remove_item();
    void add_user();
    void remove_user();
    void view_items();
    void view_hotels();
    void view_users();
    void add_manager();
    void remove_manager();
    void view_managers();
    bool search_manager(string);
    bool search_hotel(string);
    bool search_user(string);
    friend ostream& operator<<(ostream& out, Admin& admin) {
        out << "\t\t\tAdmin ID: " << admin.adminID << endl;
        // out << "\t\t\tPassword: " << admin.password << endl;
        out << "\t\t\tRole: " << admin.role << endl;
        return out; 
    }
};

// ostream& operator<<(ostream& out, Admin& admin) {
//     out << "Admin ID: " << admin.adminID << endl;
//     out << "Password: " << admin.password << endl;
//     out << "Role: " << admin.role << endl;
//     return out; 
// }
namespace admin_funcs {
    bool login(string, string);
    const string admin_db = "./Database/admins.csv";
}

namespace databases {
    // const string admin_db="./Database/admins.csv";
    const string admin_db = getenv("admin_db");
    // const string user_db="./Database/users.csv";
    const string user_db = getenv("user_db");
    // const string hotel_db="./Database/hotels.csv";
    const string hotel_db = getenv("hotel_db");
    // const string item_db="./Database/menu_";
    const string item_db = getenv("item_db");
    // const string manager_db="./Database/managers.csv";
    const string manager_db = getenv("manager_db");
    // const string deliveries_db="./Database/dell.csv";
    const string deliveries_db = getenv("deliveries_db");
    // const string undelivered_db="./Database/undelivered_queue.csv";
    const string undelivered_db = getenv("undelivered_db");
}

#endif