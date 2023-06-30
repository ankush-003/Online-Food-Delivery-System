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
    Item(string, double);
    // double getPrice();
    // string getName();
    friend ostream& operator<<(ostream&, Item&);
};
#endif