#include "Product.h"
int Product::instances = 0;
Product::Product() : id(0),name(nullptr),nameLen(0),price(0.0),quantity(0),owner(true) {
    ++instances;
}

Product::Product(int id_,const char* n,double p,int q) 
    : id(id_), name(nullptr),nameLen(0),price(p),quantity(q),owner(true) {
    if(id<0||p<0||q<0) throw std::invalid_argument("Invalid params");
    if(n) {
        nameLen=std::strlen(n);
        name=new(std::nothrow) char[nameLen+1];
        if(!name) throw std::bad_alloc();
        std::memcpy(name,n,nameLen+1);
    }
    ++instances;
}

Product::Product(const Product& other) 
    : id(other.id),name(nullptr),nameLen(other.nameLen),price(other.price),quantity(other.quantity),owner(true) {
    if(nameLen>0) {
        name=new(std::nothrow) char[nameLen + 1];
        if(!name)throw std::bad_alloc();
        std::memcpy(name,other.name,nameLen+1);
    }
    ++instances;
}

Product::Product(Product&& other) noexcept 
    : id(other.id),name(other.name),nameLen(other.nameLen),price(other.price),quantity(other.quantity),owner(other.owner) {
    other.name=nullptr; other.nameLen=0;other.owner=false;
    ++instances;
}

Product::~Product() {
    if (owner && name) delete[] name;
    --instances;
}

Product& Product::operator=(const Product& other) {
    if(this==&other) return*this;
    if(owner&&name) delete[] name;
    id=other.id;price=other.price; quantity=other.quantity;nameLen = other.nameLen;owner=true;
    if(nameLen>0){
        name=new (std::nothrow) char[nameLen+1];
        if(!name)throw std::bad_alloc();
        std::memcpy(name,other.name,nameLen + 1);
    } else name=nullptr;
    return *this;
}

Product& Product::operator=(Product&& other) noexcept {
    if(this==&other) return*this;
    if(owner && name) delete[] name;
    id=other.id; price=other.price;quantity=other.quantity;
    name=other.name; nameLen=other.nameLen;owner=other.owner;
    other.name=nullptr; other.nameLen=0; other.owner = false;
    return *this;
}

bool Product::operator==(const Product& o) const { return id == o.id; }
Product Product::shallowCopy(const Product& src) {
    Product p;
    p.id = src.id; p.name = src.name; p.nameLen = src.nameLen; p.price = src.price; p.quantity = src.quantity; p.owner = false;
    return p;
}

void Product::setQuantity(int q) {
    if (q < 0) throw std::invalid_argument("q<0");
    this->quantity = q; // using this pointer
}

void Product::changeQuantity(int delta) {
    long long n = static_cast<long long>(quantity) + delta;
    if (n < 0) throw std::runtime_error("Insufficient stock");
    quantity = static_cast<int>(n);
}

int Product::liveInstances() { return instances; }

std::ostream& operator<<(std::ostream& os, const Product& p) {
    os << p.id << ":" << (p.name ? p.name : "(no-name)") << " $" 
       << std::fixed << std::setprecision(2) << p.price 
       << " x" << p.quantity;
    return os;
}
