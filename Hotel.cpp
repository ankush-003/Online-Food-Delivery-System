#include <iostream>
#include <vector>
#include <string>
#include "Hotel.h"
using namespace std;

Item::Item(string name, int price): name(name), price(price) {}

int Item::getPrice() {
    return price;
}
string Item::getName() {
    return name;
}

ostream& operator<<(ostream& os, Item& item) {
    os << item.name << " " << item.price;
    return os;
}