class Product{
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    Product():id(0),name(""),price(0.0),quantity(0){}
    
    Product(int id,const string&name,double price,int quantity)
        : id(id),name(name),price(price),quantity(quantity){
        if(id<0||price<0||quantity<0) {   
    throw invalid_argument("Product parameters cannot be negative");
        }
    }
    
    int getId() const{return id; }
    string getName() const{return name;}
    double getPrice() const{return price;}
    int getQuantity() const{return quantity;}

    void setQuantity(int qty){
        if(qty<0) throw invalid_argument("Quantity cannot be negative");
        quantity=qty;
    }
    
    void changeQuantity(int delta){
        if(quantity+delta<0) throw runtime_error("Insufficient stock");
        quantity+=delta;
    }
    
    string toCSV() const{
        ostringstream oss;
        oss<<id<<","<<name<<","<<fixed<<setprecision(2)<<price<<","<<quantity;
        return oss.str();
    }
    
    static Product fromCSV(const string& line){
        stringstream ss(line);
        string token;
        int id,qty;
        double price;
        string name;
        if(!getline(ss,token,',')) throw runtime_error("Invalid CSV format");
        id=stoi(token);
        if(!getline(ss,name,',')) throw runtime_error("Invalid CSV format");
        
        if(!getline(ss,token,',')) throw runtime_error("Invalid CSV format");
        price=stod(token);
        if (!getline(ss,token)) throw runtime_error("Invalid CSV format");
        qty=stoi(token);
        return Product(id,name,price,qty);
    }
    
    friend ostream&operator<<(ostream& os,const Product&p) {
        os<<"ID:"<<p.id<<" | "<<p.name 
           <<" | Price: ₹" <<fixed << setprecision(2) << p.price 
           <<" | Qty: "<< p.quantity;
        return os;
    }
};
