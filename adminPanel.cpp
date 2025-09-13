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
