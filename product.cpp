// File: product.cpp
#include "product.h"
#include <iostream>
#include <new>
#include <cstring>

product::product() : id_(0), name_(nullptr), price_(0.0), qty_(0) {
}

product::product(int id, const char* nameParam, double price, int qty)
    : id_(id), name_(nullptr), price_(price), qty_(qty) {
    if (nameParam) {
        name_ = new (std::nothrow) char[MAX_NAME_LEN];
        if (name_) {
            std::strncpy(name_, nameParam, MAX_NAME_LEN - 1);
            name_[MAX_NAME_LEN - 1] = '\0';
        } else {
            id_ = 0;
            price_ = 0.0;
            qty_ = 0;
        }
    } else {
        name_ = nullptr;
    }
}

product::product(const product& other)
    : id_(other.id_), name_(nullptr), price_(other.price_), qty_(other.qty_) {
    if (other.name_) {
        name_ = new (std::nothrow) char[MAX_NAME_LEN];
        if (name_) {
            std::strncpy(name_, other.name_, MAX_NAME_LEN - 1);
            name_[MAX_NAME_LEN - 1] = '\0';
        } else {
            name_ = nullptr;
        }
    } else {
        name_ = nullptr;
    }
}

product product::shallowCopy() const {
    product p;
    p.id_ = id_;
    p.price_ = price_;
    p.qty_ = qty_;
    p.name_ = name_;
    return p;
}

product::~product() {
    if (name_) {
        delete[] name_;
        name_ = nullptr;
    }
}

product& product::operator=(const product& other) {
    if (this == &other) return *this;
    if (name_) {
        delete[] name_;
        name_ = nullptr;
    }
    id_ = other.id_;
    price_ = other.price_;
    qty_ = other.qty_;
    if (other.name_) {
        name_ = new (std::nothrow) char[MAX_NAME_LEN];
        if (name_) {
            std::strncpy(name_, other.name_, MAX_NAME_LEN - 1);
            name_[MAX_NAME_LEN - 1] = '\0';
        } else {
            name_ = nullptr;
        }
    } else {
        name_ = nullptr;
    }
    return *this;
}

bool product::operator==(const product& other) const {
    return this->id_ == other.id_;
}

product product::operator+(int addQty) const {
    product result(*this);
    result.qty_ += addQty;
    return result;
}

void product::setQty(int q) {
    this->qty_ = q;
}

void product::changeQty(int delta) {
    this->qty_ += delta;
}

void product::print() const {
    std::cout << "product{id=" << id_
              << ", name=" << (name_ ? name_ : "(null)")
              << ", price=" << price_
              << ", qty=" << qty_ << "}\n";
}

void debugproduct(const product& p) {
    std::cout << "[DEBUG] product pointer name: " << static_cast<const void*>(p.name_) << '\n';
}
