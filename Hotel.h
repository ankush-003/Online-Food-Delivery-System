#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Item {
    string name;
    int price;
    public:
    Item(string, int);
    int getPrice();
    string getName();
    friend ostream& operator<<(ostream&, Item&);
};
#endif