#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Item {
    public:
    string name;
    double price;
    int quantity;
    Item(string, double, int);
    // Item();
    // double getPrice();
    // string getName();
    friend ostream& operator<<(ostream&, Item&);
};

namespace hotel_db {
    const string hotels_db = "./Database/hotels.csv";
    const string items_db = "./Database/menu_";
    const string orders_db = "./Database/orders.csv";
}
#endif