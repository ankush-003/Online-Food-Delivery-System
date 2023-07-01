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
    static void add_hotel();
    static void remove_hotel();
    static void add_item();
    static void remove_item();
    static void add_user();
    static void remove_user();
    static void view_items();
    static void view_hotels();
    static void view_users();
    static void add_manager();
    static void remove_manager();
    static void view_managers();
    static bool search_manager(string);
    static bool search_hotel(string);
    static bool search_user(string);
};

namespace admin_funcs {
    bool login(string, string);
    const string admin_db = "./Database/admins.csv";
}

#endif