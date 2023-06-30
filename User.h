
#include <vector>
#include <string>
#include "Hotel.h"
using namespace std;
#ifndef USER_H
#define USER_H
class User {
    string password;
    public:
    static int count;
    string userID;
    string selectedHotel;
    vector<Item> allItems;
    vector<Item> cart;
    User(string, string);
    void select_hotel();
    void list_items();
    void add_item();
    void remove_item();
    void view_items();
    void view_bill();
    friend ostream& operator<<(ostream&, User&);
};



namespace user_funcs {
    void login();
    void registerUser();
    void forgot();
}

namespace global_func {
    template <typename T>
    void get_input(T&);
}
#endif