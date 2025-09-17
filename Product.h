#ifndef PRODUCT_H
#define PRODUCT_H

#include <cstddef>

constexpr std::size_t MAX_NAME_LEN = 256;

class product {
    int id_;
    char* name_;
    double price_;
    int qty_;

public:
    product();
    product(int id, const char* name, double price, int qty);
    product(const product& other);
    product shallowCopy() const;
    ~product();

    product& operator=(const product& other);
    bool operator==(const product& other) const;
    product operator+(int addQty) const;

    inline int getId() const { return id_; }
    inline const char* getName() const { return name_; }
    inline double getPrice() const { return price_; }
    inline int getQty() const { return qty_; }

    void setQty(int q);
    void changeQty(int delta);

    void print() const;

    friend void debugproduct(const product& p);
};

#endif // PRODUCT_H
