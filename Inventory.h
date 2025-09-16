#ifndef INVENTORY_H
#define INVENTORY_H
#include "Product.h"
#include <vector>

class Inventory{
private:
    std::vector<Product>products;
public:
    Inventory()=default;
    void addProduct(const Product& p);
    void addProduct(int id,const char*name,double price,int qty);

    bool has(int id) const;
    Product get(int id) const;
    void reduce(int id,int amount=1);
    const std::vector<Product>& listAll() const;
    void saveToFile(const char*path) const;
    void loadFromFile(const char*path);
};

#endif
