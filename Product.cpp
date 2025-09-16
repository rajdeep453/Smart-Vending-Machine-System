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

// void Product::writeBinary(std::ostream& os) const {
//     int32_t id_ = id; os.write(reinterpret_cast<const char*>(&id_), sizeof(id_));
//     uint32_t nlen = static_cast<uint32_t>(nameLen); os.write(reinterpret_cast<const char*>(&nlen), sizeof(nlen));
//     if (nlen) os.write(name, static_cast<std::streamsize>(nlen));
//     double pr = price; os.write(reinterpret_cast<const char*>(&pr), sizeof(pr));
//     int32_t q = quantity; os.write(reinterpret_cast<const char*>(&q), sizeof(q));
//     if (!os) throw std::runtime_error("write error");
// }

// Product Product::readBinary(std::istream& is) {
//     int32_t id_; if (!is.read(reinterpret_cast<char*>(&id_), sizeof(id_))) throw std::runtime_error("read id");
//     uint32_t nlen; if (!is.read(reinterpret_cast<char*>(&nlen), sizeof(nlen))) throw std::runtime_error("read nlen");
//     char* buf = nullptr;
//     if (nlen > 0) {
//         buf = new (std::nothrow) char[nlen+1];
//         if (!buf) throw std::bad_alloc();
//         if (!is.read(buf, static_cast<std::streamsize>(nlen))) { delete[] buf; throw std::runtime_error("read name"); }
//         buf[nlen] = '\0';
//     }
//     double pr; if (!is.read(reinterpret_cast<char*>(&pr), sizeof(pr))) { if (buf) delete[] buf; throw std::runtime_error("read price"); }
//     int32_t q; if (!is.read(reinterpret_cast<char*>(&q), sizeof(q))) { if (buf) delete[] buf; throw std::runtime_error("read qty"); }
//     Product p; p.id = id_; p.price = pr; p.quantity = q; p.nameLen = nlen;
//     if (nlen>0) { p.name = buf; p.owner = true; } else { if (buf) delete[] buf; p.name = nullptr; p.owner = true; }
//     return p;
}
