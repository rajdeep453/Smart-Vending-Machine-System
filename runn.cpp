#include <iostream>
#include <cstring>
#include <new>
#include <stdexcept>
#include <ctime>

using namespace std;

#define MAX_NAME_LEN 64
#define MAX_PRODUCTS 20

class product
{
    int id;
    char *name;
    double price;
    int qty;

public:
friend void showProduct(const product &p);
    product() : id(0), name(nullptr), price(0.0), qty(0) {}
    product(int pid, const char *pname, double pprice, int pqty)
        : id(pid), price(pprice), qty(pqty)
    {
        name = new char[MAX_NAME_LEN];
        if (name)
        {
            std::strncpy(name, pname ? pname : "", MAX_NAME_LEN - 1);
            name[MAX_NAME_LEN - 1] = '\0';
        }
        else
        {
            id = 0;
            price = 0.0;
            qty = 0;
        }
    }
    product(const product &o) : id(o.id), price(o.price), qty(o.qty)
    {
        if (o.name)
        {
            name = new (std::nothrow) char[MAX_NAME_LEN];
            if (name)
                std::strncpy(name, o.name, MAX_NAME_LEN - 1), name[MAX_NAME_LEN - 1] = '\0';
            else
                name = nullptr;
        }
        else
            name = nullptr;
    }
    ~product()
    {
        if (name)
            delete[] name;
    }
    product &operator=(const product &o)
    {
        if (this == &o)
            return *this;
        if (name)
            delete[] name;
        id = o.id;
        price = o.price;
        qty = o.qty;
        if (o.name)
        {
            name = new (std::nothrow) char[MAX_NAME_LEN];
            if (name)
                std::strncpy(name, o.name, MAX_NAME_LEN - 1), name[MAX_NAME_LEN - 1] = '\0';
        }
        else 
            name = nullptr;
        return *this;
    }
    int getId() const { return id; }
    const char *getName() const { return name; }
    double getPrice() const { return price; }
    int getQty() const { return qty; }
    void changeQty(int d) { qty += d; }
    void print() const { cout << "product{id=" << id << ", name=" << (name ? name : "(null)") << ", price=" << price << ", qty=" << qty << "}\n"; }
};

class inventory
{
    product *items[MAX_PRODUCTS];
    int cap;
    static int total;

public:
    inventory() : cap(MAX_PRODUCTS)
    {
        for (int i = 0; i < MAX_PRODUCTS; ++i)
            items[i] = nullptr;
    }
    ~inventory()
    {
        for (int i = 0; i < MAX_PRODUCTS; ++i)
            if (items[i])
            {
                delete items[i];
                items[i] = nullptr;
            }
    }
    void add(int id, const char *name, double price, int qty)
    {
        for (int i = 0; i < cap; ++i)
            if (items[i] && items[i]->getId() == id)
            {
                items[i]->changeQty(qty);
                return;
            }
        for (int i = 0; i < cap; ++i)
            if (!items[i])
            {
                items[i] = new (std::nothrow) product(id, name, price, qty);
                if (items[i])
                    ++total;
                return;
            }
        cerr << "inventory full\n";
    }
    bool has(int id) const
    {
        for (int i = 0; i < cap; ++i)
            if (items[i] && items[i]->getId() == id)
                return true;
        return false;
    }
    product get(int id) const
    {
        for (int i = 0; i < cap; ++i)
            if (items[i] && items[i]->getId() == id)
                return product(*items[i]);
        throw runtime_error("not found");
    }
    void reduce(int id, int amt = 1)
    {
        for (int i = 0; i < cap; ++i)
            if (items[i] && items[i]->getId() == id)
            {
                if (items[i]->getQty() < amt)
                    throw runtime_error("insufficient");
                items[i]->changeQty(-amt);
                return;
            }
  
    }
    void restock(int id, int amt)
    {
        for (int i = 0; i < cap; ++i)
            if (items[i] && items[i]->getId() == id)
            {
                items[i]->changeQty(amt);
                return;
            }
    
    }
    void listAll() const
    {
        cout << "Inventory:\n";
        for (int i = 0; i < cap; ++i)
            if (items[i])
                items[i]->print();
    }
    static int totalProducts() { return total; }
};

int inventory::total = 0;

enum class vmstate
{
    idle,
    selecting,
    payment_waiting,
    dispensing,
    out_of_service
};

class ipayment
{
public:
    virtual bool pay(double) = 0;
    virtual const char *methodName() const = 0;
    virtual ~ipayment() {}
    friend class simplepay;
};
class vending
{
    inventory *inv;
    vmstate state;
    int sel;
public:
    vending(inventory *i) : inv(i), state(vmstate::idle), sel(-1) {}
    vmstate getState() const { return state; }
    void enterSelection()
    {
        if (state != vmstate::idle)
            throw runtime_error("invalid");
        state = vmstate::selecting;
    }
    void selectProduct(int id)
    {
     
        product p = inv->get(id);
        if (p.getQty() <= 0)
        {
            state = vmstate::idle;
          
        }
        sel = id;
        state = vmstate::payment_waiting;
    }
    bool acceptPayment(ipayment *m)
    {
        if (state != vmstate::payment_waiting)
          
        if (!inv->has(sel))
        {
            state = vmstate::idle;
         
        }
        product p = inv->get(sel);
        bool ok = m->pay(p.getPrice());
        if (ok)
            state = vmstate::dispensing;
        return ok;
    }
    void dispense()
    {
        
         
        inv->reduce(sel, 1);
        sel = -1;
        state = vmstate::idle;
    }
    void setOut() { state = vmstate::out_of_service; }
    bool available() const { return state != vmstate::out_of_service; }
};
int readInt()
{
    int x;
    while (!(cin >> x))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "enter a valid number: ";
    }
    return x;
}

double readDouble()
{
    double x;
    while (!(cin >> x))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "enter a valid number: ";
    }
    return x;
}
void showProduct(const product &p)
{
    cout << "[friend] id=" << p.id
         << ", name=" << (p.name ? p.name : "(null)")
         << ", price=" << p.price
         << ", qty=" << p.qty << '\n';
}
void showMenu()
{
    cout << "\nMenu:\n1 List products\n2 Add product\n3 Buy product\n4 Restock product\n5 Show total products\n6 Exit\nChoose: ";
}

int main()
{
    inventory inv;
    inv.add(1, "Water", 20.0, 3);
    inv.add(2, "Soda", 30.0, 2);
    vending vm(&inv);
    bool running = true;
    while (running)
    {
        showMenu();
        int choice = readInt();
        switch (choice)
        {
        case 1:
            inv.listAll();
            break;
        case 2:
        {
            cout << "Enter id: ";
            int id = readInt();
            cout << "Enter name : ";
            char name[MAX_NAME_LEN];
            cin >> name;
            cout << "Enter price: ";
            double price = readDouble();
            cout << "Enter qty: ";
            int qty = readInt();
            inv.add(id, name, price, qty);
            cout << "Product added or restocked.\n";
            break;
        }
        case 3:
        {
            cout << "Enter product id to buy: ";
            int id = readInt();
            if (!inv.has(id))
            {
                cout << "Error: product not found.\n";
                break;
            }
            product p = inv.get(id);
            if (p.getQty() <= 0)
            {
                cout << "Error: out of stock\n";
                break;
            }
            cout << "Price is " << p.getPrice() << ". Enter cash amount: ";
            double given = readDouble();
            if (given >= p.getPrice())
            {
                // safe to reduce because we checked qty
                inv.reduce(id, 1);
                cout << "Dispensed " << p.getName() << ". Thank you.\n";
            }
            else
            {
                cout << "Payment insufficient. Transaction cancelled.\n";
            }
            break;
        }
        case 4:
        {
            cout << "Enter id to restock: ";
            int id = readInt();
            cout << "Enter amount to add: ";
            int amt = readInt();
            if (inv.has(id))
            {
                inv.restock(id, amt);
                cout << "Restocked.\n";
            }
            else
            {
                cout << "Product not found; adding new product. Enter name: ";
                char name[MAX_NAME_LEN];
                cin >> name;
                cout << "Enter price: ";
                double price = readDouble();
                inv.add(id, name, price, amt);
                cout << "Product added.\n";
            }
            break;
        }
        case 5:
            cout << "Total products added: " << inventory::totalProducts() << "\n";
            break;
        case 6:
            running = false;
            break;
        default:
            cout << "Invalid choice\n";
        }
    }
    return 0;
}
