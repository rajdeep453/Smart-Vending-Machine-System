#define MAX_PRODUCTS 20

class admin;

class inventory {
private:
    product* products_[MAX_PRODUCTS];
    int capacity_;
    static int totalProducts_;
public:
    inventory();
    ~inventory();
    void addProduct(const product& p);
    void addProduct(int id, const char* name, double price, int qty);
    bool has(int id) const;
    product get(int id) const;
    void reduce(int id, int amount = 1);
    void listAll() const;
    static int getTotalProducts();
    friend void debuginventory(const inventory& inv);
    friend class admin;
};
