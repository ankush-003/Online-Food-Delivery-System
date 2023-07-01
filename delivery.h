
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

#ifndef DELIVERY_H
#define DELIVERY_H

template <typename T>
vector<T> readCSV(const string &filename)
{
    vector<T> items;
    ifstream file(filename);
    if (file)
    {
        T item;
        while (getline(file, item))
        {
            items.push_back(item);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open the " << filename << " file.\n";
    }
    return items;
}

// class DeliveryApp {
// private:

// public:
//     queue<string> deliveryQueue;
//     vector<string> items;
//     DeliveryApp();

//     void addItemToQueue(int choice);

//     void displayDeliveryQueue() const;

//     void markItemDelivered(int deliveredChoice);

//     void saveItemsToCSV() const;

//     void saveDeliveryQueueToCSV() const;

//     friend int getDeliveryChoice();

//     friend ostream& operator<<(ostream& os, const DeliveryApp& deliveryApp);

//     vector<string>& getItems() const;
// };

class DeliveryApp
{
    queue<string> deliveryQueue;
    vector<string> items;
public:
    DeliveryApp() : items(readCSV<string>("./Database/dell.csv")) {}

    void addItemToQueue(int choice)
    {
        if (choice > 0 && choice <= static_cast<int>(items.size()))
        {
            string item = items[choice - 1];
            cout << "--------------------------------------------------------\n";
            cout << "\nAdding item to the delivery queue: " << item << endl;
            cout << "--------------------------------------------------------";
            deliveryQueue.push(item);
            items.erase(items.begin() + choice - 1);
        }
        else
        {
            cout << "\nInvalid choice.\n";
        }
    }

    void displayDeliveryQueue() const
    {
        int index = 1;
        queue<string> tempQueue = deliveryQueue;
        cout << "\nItems in the delivery queue:\n";
        while (!tempQueue.empty())
        {
            cout << index++ << ". " << tempQueue.front() << endl;
            tempQueue.pop();
        }
    }

    void markItemDelivered(int deliveredChoice)
    {
        if (deliveredChoice > 0 && deliveredChoice <= static_cast<int>(deliveryQueue.size()))
        {
            // Remove the delivered items from the queue
            int removeCount = deliveredChoice;
            while (removeCount > 0)
            {
                deliveryQueue.pop();
                removeCount--;
            }

            cout << "--------------------------------------------------------\n";
            cout << "\nItem delivered and removed from the queue.\n";
            cout << "--------------------------------------------------------\n\n";
        }
        else
        {
            cout << "\nInvalid choice.\n";
        }
    }

    void saveItemsToCSV() const
    {
        ofstream outFile("./Database/dell.csv");
        if (outFile)
        {
            for (const string &item : items)
            {
                outFile << item << endl;
            }
            outFile.close();
        }
        else
        {
            cout << "\nUnable to update the dell.csv file.\n";
        }
    }

    void saveDeliveryQueueToCSV() const
    {
        ofstream queueFile("undelivered_queue.csv");
        if (queueFile)
        {
            queue<string> tempQueue = deliveryQueue;
            while (!tempQueue.empty())
            {
                queueFile << tempQueue.front() << endl;
                tempQueue.pop();
            }
            queueFile.close();
        }
        else
        {
            cout << "\nUnable to update the delivery_queue.csv file.\n";
        }
    }
    const vector<string> &getItems() const
    {
        return items;
    }
    // Friend function to get the user's choice for item delivery
    friend ostream &operator<<(ostream &os, DeliveryApp &deliveryApp);
};

// Friend function to get the user's choice for item delivery
int getDeliveryChoice();

#endif // !DELIVERY_H