class Transaction :public Product {
    int tid;         
    int productId;   
    int qtySold;     
    float total;      

public:
    void makeTransaction() {
        string pname;
        int pid, qty;

        cout << "Enter Product ID: ";
        cin >> pid;
        cin.ignore(); 
        cout << "Enter Product Name: ";
        getline(cin, pname);
        cout << "Enter Quantity: ";
        cin >> qty;

        
        ifstream fin("products.txt");
        vector<Product> products;
        bool found = false;
        int pQty = 0;
        double price = 0.0;

        int fileId;
        string fileName;
        double filePrice;
        int fileQty;

        while (fin >> fileId >> fileName >> filePrice >> fileQty) {
            products.push_back(Product(fileId, fileName, filePrice, fileQty));
            if (fileId == pid && fileName == pname) {
                found = true;
                pQty = fileQty;
                price = filePrice;
            }
        }
        fin.close();

        if (!found) {
            cout << "\nProduct not found!\n";
            return;
        }

        if (qty > pQty) {
            cout << "\nNot enough stock available!\n";
            return;
        }

        
        double money;
        cout << "\nTotal Price: " << price * qty << endl;
        cout << "Enter amount to pay: ";
        cin >> money;

        if (money < price * qty) {
            cout << "Insufficient payment! Transaction cancelled.\n";
            return;
        }

        double change = money - (price * qty);
        cout << "Payment successful! Change: " << change << endl;

        
        for (auto &prod : products) {
            if (prod.getId() == pid && prod.getName() == pname) {
                prod.setQuantity(prod.getQuantity() - qty);
                break;
            }
        }

        ofstream fout("Temp.txt");
        for (auto &prod : products) {
            fout << prod.getId() << " " << prod.getName() << " "
                 << prod.getPrice() << " " << prod.getQuantity() << endl;
        }
        fout.close();

        remove("products.txt");
        rename("Temp.txt", "products.txt");

       
        tid = rand() % 10000; 
        ofstream receipt("receipt.txt", ios::app);
        receipt << "TID:" << tid 
                << " Product:" << pname 
                << " Qty:" << qty 
                << " Price:" << price 
                << " Total:" << price * qty << endl;
        receipt.close();

        cout << "\nTransaction completed and receipt saved.\n";
    }
};
