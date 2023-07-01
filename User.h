
#include <vector>
#include <string>
#include "Hotel.h"
using namespace std;
#ifndef USER_H
#define USER_H
class User {
    string password;
    public:
    static string user_db;
    static int count;
    string userID;
    string selectedHotel;
    string Address;
    string Phone;
    vector<Item> allItems;
    vector<Item> cart;
    double total;
    User(string, string, string, string);
    ~User(); // Destructor
    User(){}; // Default constructor
    void select_hotel();
    void list_items();
    void add_item();
    void remove_item();
    void view_items();
    void view_bill();
    bool checkout();
    // virtual void view_users() {
    //     cout << "You are not an admin!" << endl;
    // }
    friend ostream& operator<<(ostream&, User&);
};


namespace user_funcs {
    void login();
    void registerUser();
    void forgot();
}

namespace global_funcs {
    inline void input_flush() {
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.ignore(1000, '\n');
    }
    template <typename T>
    void get_input(T& var, string prompt = "") {
        cout << prompt;
        if(!(cin >> var)) {
            cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            return;
        }
    }
}
#endif