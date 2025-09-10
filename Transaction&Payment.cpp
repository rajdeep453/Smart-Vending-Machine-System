#include <iostream>
#include <vector>
#include <string>
using namespace std;

// -------------------- Item Class --------------------
class Item {
    string name;
    int code;
    double price;
    int quantity;
public:
    Item(string n, int c, double p, int q) : name(n), code(c), price(p), quantity(q) {}
    string getName() { return name; }
    int getCode() { return code; }
    double getPrice() { return price; }
    int getQuantity() { return quantity; }
    bool isAvailable() { return quantity > 0; }
    void reduceQuantity() { if(quantity > 0) quantity--; }
};

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

// -------------------- Person Base Class --------------------
class Person {
protected:
    string name;
public:
    Person(string n) : name(n) {}
    virtual void displayRole() { cout << "I am a person." << endl; }
};

// -------------------- User (Derived) --------------------
class User : public Person {
public:
    User(string n) : Person(n) {}
    void displayRole() override { cout << "I am a user. My name is " << name << endl; }
    void buyItem(VendingMachine &vm, int code, Payment &payment) {
        Item* item = vm.selectItem(code);
        if(item) {
            if(payment.processPayment(item->getPrice())) {
                vm.dispenseItem(item);
            }
        } else {
            cout << "Item not available!" << endl;
        }
    }
};

// -------------------- Admin (Derived) --------------------
class Admin : public Person {
public:
    Admin(string n) : Person(n) {}
    void displayRole() override { cout << "I am an Admin. My name is " << name << endl; }
    void restockItem(VendingMachine &vm, Item item) {
        vm.addItem(item);
        cout << "Admin added " << item.getName() << " to the machine.\n";
    }
};

// -------------------- Main --------------------
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
