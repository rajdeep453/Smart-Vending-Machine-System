#include "Inventory.h"
#include <cstdio>

void Inventory::addProduct(const Product& p) {
    for(auto& it:products)
        if(it.getId()==p.getId()){
            const_cast<Product&>(it).changeQuantity(p.getQuantity());
            return;
        }
    products.push_back(p);
}

void Inventory::addProduct(int id,const char*name,double price,int qty) {
    addProduct(Product(id,name,price,qty));
}

bool Inventory::has(int id) const{
    for(const auto& p:products) if(p.getId()==id) return true;
    return false;
}

Product Inventory::get(int id) const {
    for(const auto& p:products) if(p.getId()==id) return p;
    throw std::runtime_error("not found");
}

void Inventory::reduce(int id,int amount) {
    for(auto& p:products) 
        if(p.getId()==id) { 
            if(p.getQuantity()<amount) throw std::runtime_error("insufficient");
            p.changeQuantity(-amount); return;
        }
    throw std::runtime_error("not found");
}

const std::vector<Product>& Inventory::listAll() const { return products; }

void Inventory::saveToFile(const char*path) const {
    std::string tmp=std::string(path)+".tmp";
    std::ofstream ofs(tmp,std::ios::binary); 
    if(!ofs.is_open()) throw std::runtime_error("open fail");
    uint32_t cnt=static_cast<uint32_t>(products.size());
    ofs.write(reinterpret_cast<const char*>(&cnt), sizeof(cnt));
    for (const auto& p:products) p.writeBinary(ofs);
    ofs.close();
    if (std::rename(tmp.c_str(),path)!=0) { std::remove(tmp.c_str());throw std::runtime_error("replace fail"); }
}

void Inventory::loadFromFile(const char*path) {
    products.clear();
    std::ifstream ifs(path,std::ios::binary); 
    if (!ifs.is_open()) throw std::runtime_error("open fail");
    uint32_t cnt; if (!ifs.read(reinterpret_cast<char*>(&cnt), sizeof(cnt))) throw std::runtime_error("read cnt");
    products.reserve(cnt);
    for (uint32_t i=0;i<cnt;++i) { Product p = Product::readBinary(ifs); products.push_back(std::move(p)); }
}
