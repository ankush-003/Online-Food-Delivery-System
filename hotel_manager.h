#include <vector>
#include <string>
#include "Hotel.h"
//#include "User.h"
using namespace std;
#ifndef HOTEL_MANAGER
#define HOTEL_MANAGER


class Menu_Item
{
    public:
        string name;
        double price;
        Menu_Item(const string &item_name, double item_price);
};

class Hotel_Manager
{
    string manager_name;
    string hotel_name;


    public:
    static string menu_database_file;
    static string manager_database_file;

    Hotel_Manager(const string &name, const string &hname);
    static void manager_menu();
    void add_item_to_menu(const string &item_name, double item_price);
    void delete_item_from_menu(const string &item_name);
    //friend ostream& operator<<(ostream&, User&);

};
#endif
