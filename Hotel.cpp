#include <iostream>
#include <vector>
#include <string>
#include "Hotel.h"
using namespace std;

Item::Item(string name, double price, int quantity = 0): name(name), price(price), quantity(quantity) {}

// int Item::getPrice() {
//     return price;
// }
// string Item::getName() {
//     return name;
// }

ostream& operator<<(ostream& os, Item& item) {
    os << "Item name: " << item.name << " " << "₹ " << item.price;
    return os;
}