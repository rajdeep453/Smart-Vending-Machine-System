#include <iostream>
#include <stdexcept>
#include <new>
#include <cstring>r

#define MAX_PRODUCTS 20

class inventory {
private:
    product* products_[MAX_PRODUCTS];
    int capacity_;
    static int totalProducts_;
public:
    inventory() : capacity_(MAX_PRODUCTS) {
        for (int i = 0; i < MAX_PRODUCTS; ++i) products_[i] = nullptr;
    }
    ~inventory() {
        for (int i = 0; i < MAX_PRODUCTS; ++i) {
            if (products_[i]) {
                delete products_[i];
                products_[i] = nullptr;
            }
        }
    }
    void addProduct(const product& p) {
        for (int i = 0; i < capacity_; ++i) {
            if (products_[i] == nullptr) {
                products_[i] = new(std::nothrow) product(p);
                if (products_[i] != nullptr) {
                    totalProducts_++;
                }
                return;
            }
        }
        std::cerr << "Inventory full - cannot add product\n";
    }
    void addProduct(int id, const char* name, double price, int qty) {
        product p(id, name, price, qty);
        addProduct(p);
    }
    bool has(int id) const {
        for (int i = 0; i < capacity_; ++i) {
            if (products_[i] && products_[i]->getId() == id) return true;
        }
        return false;
    }
    product get(int id) const {
        for (int i = 0; i < capacity_; ++i) {
            if (products_[i] && products_[i]->getId() == id) {
                return product(*products_[i]);
            }
        }
        throw std::runtime_error("Product not found in inventory");
    }
    void reduce(int id, int amount = 1) {
        for (int i = 0; i < capacity_; ++i) {
            if (products_[i] && products_[i]->getId() == id) {
                if (products_[i]->getQty() < amount) {
                    throw std::runtime_error("Insufficient stock");
                }
                products_[i]->changeQty(-amount);
                return;
            }
        }
        throw std::runtime_error("Product not found");
    }
    void listAll() const {
        std::cout << "Inventory list:\n";
        for (int i = 0; i < capacity_; ++i) {
            if (products_[i]) products_[i]->print();
        }
    }
    static int getTotalProducts() {
        return totalProducts_;
    }
    friend void debuginventory(const inventory& inv);
};

int inventory::totalProducts_ = 0;

void debuginventory(const inventory& inv) {
    std::cout << "[DEBUG] Inventory pointers:\n";
    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        std::cout << " slot " << i << " -> " << static_cast<const void*>(inv.products_[i]) << "\n";
    }
}
