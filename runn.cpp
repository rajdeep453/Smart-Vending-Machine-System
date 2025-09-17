#include <iostream>
#include <cstring>
#include <new>
#include <stdexcept>
#include <ctime>

#define MAX_NAME_LEN 64
#define MAX_PRODUCTS 20

class product {
    int id;
    char* name;
    double price;
    int qty;
public:
    product(): id(0), name(nullptr), price(0.0), qty(0) {}
    product(int pid, const char* pname, double pprice, int pqty)
    : id(pid), price(pprice), qty(pqty) {
        name = new(std::nothrow) char[MAX_NAME_LEN];
        if (name) {
            std::strncpy(name, pname ? pname : "", MAX_NAME_LEN - 1);
            name[MAX_NAME_LEN - 1] = '\0';
        } else {
            id = 0; price = 0.0; qty = 0;
        }
    }
    product(const product& o): id(o.id), price(o.price), qty(o.qty) {
        if (o.name) {
            name = new(std::nothrow) char[MAX_NAME_LEN];
            if (name) std::strncpy(name, o.name, MAX_NAME_LEN - 1), name[MAX_NAME_LEN - 1] = '\0';
            else name = nullptr;
        } else name = nullptr;
    }
    ~product() { if (name) delete [] name; }
    product& operator=(const product& o) {
        if (this == &o) return *this;
        if (name) delete [] name;
        id = o.id; price = o.price; qty = o.qty;
        if (o.name) { name = new(std::nothrow) char[MAX_NAME_LEN]; if (name) std::strncpy(name, o.name, MAX_NAME_LEN-1), name[MAX_NAME_LEN-1]='\0'; }
        else name = nullptr;
        return *this;
    }
    int getId() const { return id; }
    const char* getName() const { return name; }
    double getPrice() const { return price; }
    int getQty() const { return qty; }
    void changeQty(int d) { qty += d; }
    void print() const { std::cout << "product{id=" << id << ", name=" << (name?name:"(null)") << ", price=" << price << ", qty=" << qty << "}\n"; }
};

class inventory {
    product* items[MAX_PRODUCTS];
    int cap;
    static int total;
public:
    inventory(): cap(MAX_PRODUCTS) { for (int i=0;i<MAX_PRODUCTS;++i) items[i]=nullptr; }
    ~inventory(){ for (int i=0;i<MAX_PRODUCTS;++i) if (items[i]) { delete items[i]; items[i]=nullptr; } }
    void add(int id,const char* name,double price,int qty){
        for(int i=0;i<cap;++i) if(!items[i]){ items[i]=new(std::nothrow) product(id,name,price,qty); if(items[i]) ++total; return; }
        std::cerr<<"inventory full\n";
    }
    bool has(int id) const { for(int i=0;i<cap;++i) if(items[i] && items[i]->getId()==id) return true; return false; }
    product get(int id) const { for(int i=0;i<cap;++i) if(items[i] && items[i]->getId()==id) return product(*items[i]); throw std::runtime_error("not found"); }
    void reduce(int id,int amt=1){ for(int i=0;i<cap;++i) if(items[i] && items[i]->getId()==id){ if(items[i]->getQty()<amt) throw std::runtime_error("insufficient"); items[i]->changeQty(-amt); return; } throw std::runtime_error("not found"); }
    void listAll() const { std::cout<<"Inventory:\n"; for(int i=0;i<cap;++i) if(items[i]) items[i]->print(); }
    static int totalProducts(){ return total; }
};

int inventory::total = 0;

enum class vmstate { idle, selecting, payment_waiting, dispensing, out_of_service };

class ipayment { public: virtual bool pay(double)=0; virtual const char* methodName() const=0; virtual ~ipayment(){} };

class vending {
    inventory* inv;
    vmstate state;
    int sel;
public:
    vending(inventory* i): inv(i), state(vmstate::idle), sel(-1) {}
    vmstate getState() const { return state; }
    void enterSelection(){ if(state!=vmstate::idle) throw std::runtime_error("invalid"); state=vmstate::selecting; }
    void selectProduct(int id){ if(state!=vmstate::selecting) throw std::runtime_error("invalid"); if(!inv->has(id)){ state=vmstate::idle; throw std::runtime_error("not found"); } product p=inv->get(id); if(p.getQty()<=0){ state=vmstate::idle; throw std::runtime_error("out of stock"); } sel=id; state=vmstate::payment_waiting; }
    bool acceptPayment(ipayment* m){ if(state!=vmstate::payment_waiting) throw std::runtime_error("invalid"); if(!inv->has(sel)){ state=vmstate::idle; throw std::runtime_error("gone"); } product p=inv->get(sel); bool ok=m->pay(p.getPrice()); if(ok) state=vmstate::dispensing; return ok; }
    void dispense(){ if(state!=vmstate::dispensing) throw std::runtime_error("invalid"); inv->reduce(sel,1); sel=-1; state=vmstate::idle; }
    void setOut() { state=vmstate::out_of_service; }
    bool available() const { return state!=vmstate::out_of_service; }
};

class simplepay : public ipayment {
    bool ok;
public:
    simplepay(bool s=true): ok(s) {}
    bool pay(double){ return ok; }
    const char* methodName() const override { return "simple"; }
};

int main(){
    inventory inv;
    inv.add(1,"Water",20.0,3);
    inv.add(2,"Soda",30.0,2);
    inv.listAll();
    vending vm(&inv);
    try{
        vm.enterSelection();
        std::cout<<"entered selection\n";
        vm.selectProduct(1);
        std::cout<<"selected 1\n";
        simplepay sp(true);
        if(vm.acceptPayment(&sp)){
            std::cout<<"payment ok\n";
            vm.dispense();
            std::cout<<"dispensed\n";
        } else std::cout<<"payment declined\n";
    } catch(const std::exception& e){ std::cout<<"error: "<<e.what()<<"\n"; }
    std::cout<<"\nAfter dispense:\n";
    inv.listAll();
    try{
        vm.enterSelection();
        vm.selectProduct(2);
        simplepay sp2(false);
        if(!vm.acceptPayment(&sp2)) std::cout<<"declined path works\n";
    } catch(const std::exception& e){ std::cout<<"error: "<<e.what()<<"\n"; }
    return 0;
}
