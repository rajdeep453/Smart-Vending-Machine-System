#include <iostream>
#include <string>
#include <ctime>
#include<bits/stdc++.h>
#include<bits/stdc++.h>
using namespace std;


#define SUCCESS 1
#define FAILURE 0

using namespace std;
class product;
class product{
 static int id;
 string name;
int price;
string catogery;
bool isavail;
string descrip;

public:

product(){
id = id+1;
isavail=true;
}
product(int price, string name, string cat,string d){
price=price;
id=id+1;
name=name;
catogery=cat;
descrip=d;
isavail=true;
}
product(int price, string name, string cat){
price=price;
id=id+1;
name=name;
catogery=cat;
descrip="description is not given";
isavail=true;
}

}

;
class slot{
    public:
int slotid;
int productid;
int quantity;
int capacity;
void restock(int amount){
    if(amount+quantiy >capacity){
        cout<<"stock is  added and it is full"
    }
    quantity=max(quantity+amount,capacity);
}
bool dispense(int q){
    if(q<=quantity) quantity -= q;
    else {
        cout<<"insufficient stock ,only"<<quantity<<"items left"<<endl;
    }
}




};
// class transaction{
//     int txid;
//     int slotid;
//     int productid;
//     int quantity;
//     int pricepaid;
//     int changegiven;
//     bool status;
     
// };

int product::id=0;

class Transaction;  
class product;

class VendingMachine {
private:
    static int transactionCount; 
    int productId;
    string productName;
    double price;

public:
    
    VendingMachine() : productId(0), productName("Unknown"), price(0.0) {}

    
    VendingMachine(int id, string name, double p) {
        productId = id;
        productName = name;
        price = p;
    }

    VendingMachine(const VendingMachine &vm) {
        productId = vm.productId;
        productName = vm.productName;
        price = vm.price;
    }

    static void showTransactionCount() {
        cout << "Total Transactions so far: " << transactionCount << endl;
    }


    double getPrice() const {
        return price;
    }

   
    inline string getProductName() { return productName; }

    
    int makePayment(double moneyInserted);                   
    int makePayment(string cardNo, string holder, int cvv);  
    int makePayment(string upiId);                           
    int makePayment(string bankName, string user, string pass); 

    
    friend class Transaction;
};


int VendingMachine::transactionCount = 0;


class Transaction {
public:
    void logTransaction(VendingMachine &vm, string method, double amount, bool status) {
        VendingMachine::transactionCount++;
        time_t now = time(0);
        cout << "\n Transaction Log \n";
        cout << "Product: " << vm.productName << endl;
        cout << "Method: " << method << endl;
        cout << "Amount: " << amount << endl;
        cout << "Status: " << (status ? "Success" : "Failed") << endl;
        cout << "Time: " << ctime(&now) << endl;
    }
};




int VendingMachine::makePayment(double moneyInserted) {
    cout << "Cash Payment Selected.\n";
    if (moneyInserted < price) return FAILURE;
    if (moneyInserted > price) cout << "Returning change: " << moneyInserted - price << endl;
    return SUCCESS;
}


int VendingMachine::makePayment(string cardNo, string holder, int cvv) {
    cout << "Processing Card Payment for " << holder << endl;
    if (cardNo.length() != 16 || cvv < 100) return FAILURE; 
    return SUCCESS;
}


int VendingMachine::makePayment(string upiId) {
    cout << "Processing UPI Payment for " << upiId << endl;
    return SUCCESS; 
}


int VendingMachine::makePayment(string bankName, string user, string pass) {
    cout << "NetBanking via " << bankName << " for user " << user << endl;
    if (pass.length() < 4) return FAILURE; 
    return SUCCESS;
}


int main() {
    VendingMachine vm(101, "Coke", 50.0);
    Transaction tx;

    int choice;
    cout << "Select Payment Method: 1.Cash 2.Card 3.UPI 4.NetBanking\n";
    cin >> choice;

    int status = FAILURE;

    switch (choice) {
        case 1: {
            double money;
            cout << "Insert Cash: ";
            cin >> money;
            status = vm.makePayment(money);
            tx.logTransaction(vm, "Cash", money, status);
            break;
        }
        case 2: {
            string cardNo, holder;
            int cvv;
            cout << "Enter Card No: "; cin >> cardNo;
            cout << "Enter Holder: "; cin >> holder;
            cout << "Enter CVV: "; cin >> cvv;
            status = vm.makePayment(cardNo, holder, cvv);
            tx.logTransaction(vm, "Card", vm.getPrice(), status);
            break;
        }
        case 3: {
            string upiId;
            cout << "Enter UPI ID: "; cin >> upiId;
            status = vm.makePayment(upiId);
            tx.logTransaction(vm, "UPI", vm.getPrice(), status);
            break;
        }
        case 4: {
            string bank, user, pass;
            cout << "Enter Bank: "; cin >> bank;
            cout << "Enter Username: "; cin >> user;
            cout << "Enter Password: "; cin >> pass;
            status = vm.makePayment(bank, user, pass);
            tx.logTransaction(vm, "NetBanking", vm.getPrice(), status);
            break;
        }
        default:
            cout << "Invalid Choice\n";
    }

    if (status == SUCCESS) {
        cout << "Dispensing product: " << vm.getProductName() << endl;
    } else {
        cout << "Payment Failed. Transaction Cancelled.\n";
    }

    VendingMachine::showTransactionCount();
    return 0;
}



