#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class product;
class product{
 static int id;
 string name;
int price;
string catogery;
bool isavail;
string descrip;

public:

product(){
id = id+1;
isavail=true;
}
product(int price, string name, string cat,string d){
price=price;
id=id+1;
name=name;
catogery=cat;
descrip=d;
isavail=true;
}
product(int price, string name, string cat){
price=price;
id=id+1;
name=name;
catogery=cat;
descrip="description is not given";
isavail=true;
}

}

;
class slot{
    public:
int slotid;
int productid;
int quantity;
int capacity;
void restock(int amount){
    if(amount+quantiy >capacity){
        cout<<"stock is  added and it is full"
    }
    quantity=max(quantity+amount,capacity);
}
bool dispense(int q){
    if(q<=quantity) quantity -= q;
    else {
        cout<<"insufficient stock ,only"<<quantity<<"items left"<<endl;
    }
}




};
class transaction{
    int txid;
    int slotid;
    int productid;
    int quantity;
    int pricepaid;
    int changegiven;
    bool status;
    transaction():txId(0),slotId(0),productId(0),pricePaid(0),changeGiven(0),timestamp(""),status("FAILED"){}
transaction(int txid,int slotid,int productId,int pricePaid,int changegiven,string ,string &st):
};
class vendingmachine(){

};
int product::id=0;
int main(){
  
    return 0;
}