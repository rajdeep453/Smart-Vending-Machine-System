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




};
int product::id=0;
int main(){
  
    return 0;
}