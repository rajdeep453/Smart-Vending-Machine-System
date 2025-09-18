#include <iostream>
#include <cstring>
#include <new>

#define MAX_NAME_LEN 64

class product {
private:
    int id;
    char* name;
    double price;
    int qty;
public:
    product() : id(0), name(nullptr), price(0.0), qty(0) {}
    product(int pid, const char* pname, double pprice, int pqty)
    : id(pid), price(pprice), qty(pqty) {
        name = new(std::nothrow) char[MAX_NAME_LEN];
        if (name == nullptr) {
            this->id = 0;
            this->price = 0.0;
            this->qty = 0;
            return;
        }
        std::strncpy(name, pname ? pname : "", MAX_NAME_LEN - 1);
        name[MAX_NAME_LEN - 1] = '\0';
    }
    product(const product& other)
    : id(other.id), price(other.price), qty(other.qty) {
        if (other.name) {
            name = new(std::nothrow) char[MAX_NAME_LEN];
            if (name) {
                std::strncpy(name, other.name, MAX_NAME_LEN - 1);
                name[MAX_NAME_LEN - 1] = '\0';
            } else {
                name = nullptr;
            }
        } else {
            name = nullptr;
        }
    }
    product shallowCopy() const {
        product p;
        p.id = id;
        p.price = price;
        p.qty = qty;
        p.name = name;
        return p;
    }
    ~product() {
        if (name) {
            delete [] name;
            name = nullptr;
        }
    }
    product& operator=(const product& other) {
        if (this == &other) return *this;
        if (name) { delete [] name; name = nullptr; }
        id = other.id;
        price = other.price;
        qty = other.qty;
        if (other.name) {
            name = new(std::nothrow) char[MAX_NAME_LEN];
            if (name) {
                std::strncpy(name, other.name, MAX_NAME_LEN - 1);
                name[MAX_NAME_LEN - 1] = '\0';
            }
        } else {
            name = nullptr;
        }
        return *this;
    }
    bool operator==(const product& other) const {
        return this->id == other.id;
    }
    product operator+(int addQty) const {
        product p(*this);
        p.qty += addQty;
        return p;
    }
    inline int getId() const { return id; }
    inline const char* getName() const { return name; }
    inline double getPrice() const { return price; }
    inline int getQty() const { return qty; }
    void setQty(int q) { this->qty = q; }
    void changeQty(int delta) { this->qty += delta; }
    void print() const {
        std::cout << "product{id=" << id << ", name=" << (name ? name : "(null)")
                  << ", price=" << price << ", qty=" << qty << "}\n";
    }
    friend void debugproduct(const product& p);
};

void debugproduct(const product& p) {
    std::cout << "[DEBUG] product name pointer: " << static_cast<const void*>(p.name) << "\n";
}
