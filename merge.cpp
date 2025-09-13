#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;




class Product
{
protected:
    int id;
    string name;
    double price;
    int quantity;

public:
    Product() {}
    Product(int pid, string pname, double pprice, int pqty)
        : id(pid), name(pname), price(pprice), quantity(pqty) {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setQuantity(int q) { quantity = q; }
    void saveToFile()
    {
        ofstream fout("products.txt", ios::app);
        fout << id << " " << name << " " << price << " " << quantity << endl;
        fout.close();
    }
    void printProduct() const
    {
        cout << left << setw(5) << id
             << setw(15) << name
             << setw(10) << price
             << setw(10) << quantity << endl;
    }
    void searchProduct()
    {
        int searchId;
        string searchName;
        cout << "Enter Product ID: ";
        cin >> searchId;
        cout << "Enter Product Name: ";
        cin >> searchName;

        ifstream fin("products.txt");
        int pid, qty;
        string pname;
        double pprice;
        bool found = false;

        while (fin >> pid >> pname >> pprice >> qty)
        {
            if (pid == searchId && pname == searchName)
            {
                cout << "\nProduct Found:\n";
                cout << left << setw(5) << pid
                     << setw(15) << pname
                     << setw(10) << pprice
                     << setw(10) << qty << endl;
                found = true;
                break;
            }
        }
        fin.close();

        if (!found)
        {
            cout << "Product with ID " << searchId
                 << " and name '" << searchName << "' not found.\n";
        }
    }
};

struct delivery
{
    string personname;
    string productName;
    int quantity;
};
class vendingmachine{
 int selectedid;
 
};
struct Delivery
{
    string personName;
    string productName;
    int quantity;
};
class transaction
{
    
};

class adminPanel : public transaction, public Product
{
public:
    void addProductToFile()
    {
        ofstream fout("products.txt", ios::app);
        fout << id << " " << name << " " << price << " " << quantity << endl;
        fout.close();
        cout << "Product added successfully.\n";
    }

    void removeProduct(const string &pname)
    {
        ifstream fin("products.txt");
        ofstream fout("temp.txt");

        string name;
        double price;
        int qty;
        bool found = false;

        while (fin >> name >> price >> qty)
        {
            if (name != pname)
            {
                fout << name << " " << price << " " << qty << endl;
            }
            else
            {
                found = true;
            }
        }
        fin.close();
        fout.close();

        remove("products.txt");
        rename("temp.txt", "products.txt");

        if (found)
            cout << pname << " removed successfully.\n";
        else
            cout << pname << " not found in stock.\n";
    }

    void printStock()
    {
        ifstream fin("products.txt");
        string name;
        double price;
        int qty;

        cout << "\n--- Stock Details ---\n";
        cout << left << setw(15) << "Product"
             << setw(10) << "Price"
             << setw(10) << "Qty" << endl;

        while (fin >> name >> price >> qty)
        {
            cout << left << setw(15) << name
                 << setw(10) << price
                 << setw(10) << qty << endl;
        }
        fin.close();
    }

    void addDelivery(const Delivery &d)
    {
        ofstream fout("delivery.txt", ios::app);
        fout << d.personName << " " << d.productName << " " << d.quantity << endl;
        fout.close();

        vector<Product> products;
        ifstream fin("products.txt");
        int pid, qty;
        string pname;
        double pprice;

        while (fin >> pid >> pname >> pprice >> qty)
        {
            products.push_back(Product(pid, pname, pprice, qty));
        }
        fin.close();

        for (auto &prod : products)
        {
            if (prod.getName() == d.productName && prod.getQuantity() >= d.quantity)
            {
                prod.setQuantity(prod.getQuantity() - d.quantity);
            }
        }

        ofstream fout2("products.txt");
        for (auto &prod : products)
        {
            fout2 << prod.getId() << " " << prod.getName() << " "
                  << prod.getPrice() << " " << prod.getQuantity() << endl;
        }
        fout2.close();
    }
};
int  main()
{
    
}
