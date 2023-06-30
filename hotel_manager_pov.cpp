#include <bits/stdc++.h>
using namespace std;

namespace Food_Delivery_Sysytem
{
class Menu_Item
{
    public:
        string name;
        double price;
        
        Menu_Item(const string& item_name, double item_price) : name(item_name), price(item_price) {}
};


class Hotel_Manager
{
    private:
        string hotel_name;
        string hotel_address;
        string menu_database_file;

    public:
        Hotel_Manager(const string& name, const string& address, const string& menufile): hotel_name(name), hotel_address(address), menu_database_file(menufile) {}

        //function to add item to menufile.

        void add_item_to_menu(const string& item_name, double item_price) 
        {
            
            ofstream menufile(menu_database_file, ios::app);         //app is append mode
            if (menufile.is_open()) 
            {
                menufile << item_name << "," << item_price << "\n";
                menufile.close();
                cout << "Item added to the menu successfully.\n";
            } 
            else 
            {
                cout << "Failed to open the menu database file.\n";
            }
        }

        //function to delete item from menufile.

        void delete_item_from_menu(const string& item_name) 
        {
            // Read the menu database file into memory
            ifstream menufile(menu_database_file);
            if (menufile.is_open())
            {
                vector<Menu_Item> Menu_Items;
                string line;
                while (getline(menufile, line)) 
                {
                    string item_name_in_file = line.substr(0, line.find(','));
                    double item_price_in_file = stod(line.substr(line.find(',') + 1));
                    Menu_Items.push_back(Menu_Item(item_name_in_file, item_price_in_file));
                }
                menufile.close();

                // Find and remove the item from the Menu_Items vector
                bool found = false;
                for (auto it = Menu_Items.begin(); it != Menu_Items.end(); ++it)
                {
                    if (it->name == item_name)
                    {
                        Menu_Items.erase(it);
                        found = true;
                        break;
                    }
                }

                // Rewrite the menu database file with updated Menu_Items
                ofstream updated_menu_file(menu_database_file);
                if (updated_menu_file.is_open()) {
                    for (const auto& item : Menu_Items) {
                        updated_menu_file << item.name << "," << item.price << "\n";
                    }
                    updated_menu_file.close();
                    if (found)
                        cout << "Item deleted from the menu successfully.\n";
                    else
                        cout << "Item not found in the menu.\n";
                } else {
                    cout << "Failed to open the menu database file.\n";
                }
            } else {
                cout << "Failed to open the menu database file.\n";
            }
        }
};
                
}


int main() 
{

    using namespace Food_Delivery_Sysytem;
     
    Hotel_Manager manager("Hotel ABC", "uehfeuh", "menu_abc.csv");  //create object of class
    
    // Add items to the menu of a particular hotel
    manager.add_item_to_menu("Pizza", 9.9);
    manager.add_item_to_menu("Burger", 6.9);
    manager.add_item_to_menu("Pasta", 20.0);
    manager.delete_item_from_menu("Burger");

    return 0;
}
