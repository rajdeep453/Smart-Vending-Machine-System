#include <iostream>
#include <stdexcept>
#include <ctime>

enum class vmstate {
    idle,
    selecting,
    payment_waiting,
    dispensing,
    out_of_service
};

class ipayment {
public:
    virtual bool pay(double amount) = 0;
    virtual const char* methodName() const = 0;
    virtual ~ipayment() {}
};

class vendingmachine {
private:
    inventory* inv;
    vmstate state;
    int selectedId;
public:
    vendingmachine(inventory* inventoryPtr) : inv(inventoryPtr), state(vmstate::idle), selectedId(-1) {}
    vmstate getState() const { return state; }
    void enterSelectionMode() {
        if (state != vmstate::idle) throw std::runtime_error("enterSelectionMode invalid");
        state = vmstate::selecting;
    }
    void selectProduct(int id) {
        if (state != vmstate::selecting) throw std::runtime_error("selectProduct invalid");
        if (!inv->has(id)) {
            state = vmstate::idle;
            throw std::runtime_error("Product not found");
        }
        product p = inv->get(id);
        if (p.getQty() <= 0) {
            state = vmstate::idle;
            throw std::runtime_error("Product out of stock");
        }
        selectedId = id;
        state = vmstate::payment_waiting;
    }
    bool acceptPayment(ipayment* method) {
        if (state != vmstate::payment_waiting) throw std::runtime_error("acceptPayment invalid");
        if (!inv->has(selectedId)) {
            state = vmstate::idle;
            throw std::runtime_error("Selected product gone");
        }
        product p = inv->get(selectedId);
        double amount = p.getPrice();
        bool ok = method->pay(amount);
        if (ok) {
            state = vmstate::dispensing;
            return true;
        } else {
            return false;
        }
    }
    void dispense() {
        if (state != vmstate::dispensing) throw std::runtime_error("dispense invalid");
        inv->reduce(selectedId, 1);
        selectedId = -1;
        state = vmstate::idle;
    }
    void setOutOfService() { state = vmstate::out_of_service; }
    bool isAvailable() const { return state != vmstate::out_of_service; }
};
