#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> 

using namespace std;

class Transaction {
protected:
    int productId;
    string productName;
    int quantity;
    float price;
    float total;

public:


    Transaction() {
        productId = 0;
        productName = "N/A";
        quantity = 0;
        price = 0.0;
        total = 0.0;
        
    }

    
    ~Transaction() {
        
    }


    void setTransaction(int pid, string pname, int qty, float pr) {
        productId = pid;
        productName = pname;
        quantity = qty;
        price = pr;
        total = qty * pr;

      
        ofstream fout("transaction.txt", ios::app);
        fout << productId << " " << productName << " "
             << quantity << " " << price << " " << total << endl;
        fout.close();
    }



    void showTransaction() {
   
   
    cout << "Product Name : " << productName << endl;
    cout << "Quantity     : " << quantity << endl;
    cout << "Price/Unit   : " << price << endl;
    cout << "Total Price  : " << total << endl;
   
}
    float getTotal() {
        return total;
    }
};

class Payment : public Transaction {
public:
    void makePayment() {
        int choice;
        cout << "\nSelect Payment Method:\n1. UPI\n2. Cash\n3. Netbanking\n4. Card\n";
        cin >> choice;

        bool success = false;
        switch (choice) {
        case 1: {
            string upi;
            cout << "Enter UPI ID: ";
            cin >> upi;
            if (upi.find('@') != string::npos) {
                cout << "UPI Payment Successful!\n";
                success = true;
            } else {
                cout << "Invalid UPI ID.\n";
            }
            break;
        }
        case 2: {
            float cash;
            cout << "Enter cash amount: ";
            cin >> cash;
            if (cash < total) {
                cout << "Payment Failed. Not enough cash.\n";
            } else {
                cout << "Cash Payment Successful! Change: " << (cash - total) << endl;
                success = true;
            }
            break;
        }
        case 3: {
           
            string banks[4] = {"SBI", "HDFC", "PNB", "YESBANK"};
            int n = 4;

            cout << "Select Bank:\n";
            for (int i = 0; i < n; i++) {
                cout << i + 1 << ". " << banks[i] << endl;
            }

            int bchoice;
            cin >> bchoice;

            if (bchoice >= 1 && bchoice <= n) {
                cout << "Payment through " << banks[bchoice - 1] << " Successful!\n";
                success = true;
            } else {
                cout << "Invalid Bank Selection.\n";
            }
            break;
        }
        case 4: {
    string holder, expiry;
    string cardNumber;
    int cvv;

    cout << "Enter Card Holder Name: ";
    cin.ignore();
    getline(cin, holder);

    cout << "Enter Card Number (16 digits): ";
    cin >> cardNumber;

   
    string digits;
    for (char c : cardNumber) {
        if (isdigit((unsigned char)c)) digits.push_back(c);
    }

   
    if (digits.size() != 16) {
        cout << "Invalid Card Number!\n";
        break;
    }

    

    cout << "Enter Expiry (MM/YY): ";
    cin >> expiry;

    cout << "Enter CVV (3 digits): ";
    cin >> cvv;

    if (cvv >= 100 && cvv <= 999) {
        cout << "Card Payment Successful!\n";

        
        ofstream rout("receipt.txt", ios::app);
        rout << "\n------ RECEIPT ------\n";
        rout << "Thanks for choosing us!\n";
        rout << "Product ID     : " << productId << endl;
        rout << "Product Name   : " << productName << endl;
        rout << "Quantity       : " << quantity << endl;
        rout << "Price per item : " << price << endl;
        rout << "Total Paid     : " << total << endl;
        rout << "Payment Method : CARD\n";
        rout << "Card Holder    : " << holder << endl;
        
        rout << "Expiry         : " << expiry << endl;
        
        rout.close();

        success = true;
    } else {
        cout << "Invalid CVV!\n";
    }
    break;
}

        default:
            float cash;
            cout << "Enter cash amount: ";
            cin >> cash;
            if (cash < total) {
                cout << "Payment Failed. Not enough cash.\n";
            } else {
                cout << "Cash Payment Successful! Change: " << (cash - total) << endl;
                success = true;
            }
            break;
        }

        if (success) {
            
            ofstream rout("receipt.txt", ios::app);
            rout << "\n------ RECEIPT ------\n";
            rout << "Thank you for choosing us!\n";
            rout << "Product ID: " << productId << endl;
            rout << "Product Name: " << productName << endl;
            rout << "Quantity: " << quantity << endl;
            rout << "Price per item: " << price << endl;
            rout << "Total Paid: " << total << endl;
            
            rout.close();

            cout << "Receipt Printed.\nDispensing Product...\n";
        }
    }
};

int main() {
    Payment p;
    p.setTransaction(101, "Chips", 2, 10.0);

    p.showTransaction();
    
    p.makePayment();
    return 0;
}

