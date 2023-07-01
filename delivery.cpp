
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include "delivery.h"
#include "User.h"

using namespace std;


// Friend function to get the user's choice for item delivery
ostream& operator<<(ostream& os, DeliveryApp& deliveryApp) {
    os << "\n\nItems waiting to be picked up:\n";
    for (size_t i = 0; i < deliveryApp.items.size(); ++i) {
        os << i + 1 << ". " << deliveryApp.items[i] << endl;
    }
    return os;
}

int getDeliveryChoice() {
    int choice;
    cout<< "--------------------------------------------------------";
    cout << "\nSelect an item to deliver (enter the item number, 0 to view delivery queue, -1 to exit): ";
    cout<< "\n--------------------------------------------------------\n";
    try {
        global_funcs::get_input(choice, "Enter your choice: ");
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }
    //cin >> choice;
    return choice;
}

/*int main() {
    DeliveryApp deliveryApp;

    cout << "\nDelivery Application\n";
    cout << "---------------------";

    while (true) {
        cout << deliveryApp;

        int choice = getDeliveryChoice();

        if (choice == -1) {
            break;
        } else if (choice == 0) {
            deliveryApp.displayDeliveryQueue();
            int deliveredChoice;
            cout << "\nEnter the item number that has been delivered (0 to continue): ";
            cin >> deliveredChoice;
            deliveryApp.markItemDelivered(deliveredChoice);
        } else {
            deliveryApp.addItemToQueue(choice);
        }
    }

    deliveryApp.saveItemsToCSV();
    deliveryApp.saveDeliveryQueueToCSV();

    cout<< "--------------------------------------------------------\n";
    cout<< "THANK YOU FOR USING THE APP";

    return 0;
}*/
