#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<new>
#include<stdexcept>
#include<iomanip>

#define DATA_FILE "data/inventory.bin"   
class Inventory;

class Product{
private:
    int id;
    char* name;         
    std::size_t nameLen;
    double price;
    int quantity;
    bool owner;           
    static int instances; 

public:
    Product();                                      
    Product(int id,const char* n,double p,int q); 
    Product(const Product& other);                   
    Product(Product&& other) noexcept;             

    ~Product();

    Product& operator=(const Product& other);
    Product& operator=(Product&& other) noexcept;

    bool operator==(const Product& other) const;

    static Product shallowCopy(const Product& src);

    inline int getId() const { return id;}
    inline const char* getName() const{ return name ? name :"(no-name)";}
    inline double getPrice() const{ return price;}
    inline int getQuantity() const{ return quantity;}

    void setQuantity(int q); 
    void changeQuantity(int delta);

    static int liveInstances();

    friend class Inventory;
    friend std::ostream& operator<<(std::ostream& os, const Product& p);

    void writeBinary(std::ostream& os) const;
    static Product readBinary(std::istream& is);
};

#endif
