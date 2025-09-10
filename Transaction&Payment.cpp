#include <iostream>
#include <vector>
#include <string>
using namespace std;



// -------------------- Abstract Payment Class --------------------
class Payment {
public:
    virtual bool processPayment(double amount) = 0; // Pure virtual -> Abstraction
};

// -------------------- Cash Payment --------------------
class CashPayment : public Payment {
    double cashInserted;
public:
    CashPayment(double c) : cashInserted(c) {}
    bool processPayment(double amount) override {
        if(cashInserted >= amount) {
            cout << "Payment successful with cash. Change: " << (cashInserted - amount) << endl;
            return true;
        }
        cout << "Insufficient cash inserted!" << endl;
        return false;
    }
};

// -------------------- Vending Machine --------------------
class VendingMachine {
    vector<Item> inventory;
public:
    void addItem(Item item) { inventory.push_back(item); }
    void showItems() {
        cout << "\n--- Available Items ---\n";
        for(auto &i : inventory) {
            cout << i.getCode() << ". " << i.getName() 
                 << " - Rs." << i.getPrice() 
                 << " (" << i.getQuantity() << " left)\n";
        }
    }
    Item* selectItem(int code) {
        for(auto &i : inventory) {
            if(i.getCode() == code && i.isAvailable()) {
                return &i;
            }
        }
        return nullptr;
    }
    void dispenseItem(Item* item) {
        if(item) {
            item->reduceQuantity();
            cout << "Dispensing: " << item->getName() << endl;
        }
    }
};

int main() {
    VendingMachine vm;

    // Admin adds items
    Admin admin("Rahul");
    admin.displayRole();
    vm.addItem(Item("Chips", 1, 20.0, 5));
    vm.addItem(Item("Soda", 2, 35.0, 3));
    vm.addItem(Item("Chocolate", 3, 25.0, 2));

    // Show items
    vm.showItems();

    // User interacts
    User user("Riya");
    user.displayRole();
    int choice;
    cout << "\nEnter item code to buy: ";
    cin >> choice;
    double money;
    cout << "Insert money: ";
    cin >> money;

    CashPayment cp(money);
    user.buyItem(vm, choice, cp);

    vm.showItems(); // Show updated stock
    return 0;
}

