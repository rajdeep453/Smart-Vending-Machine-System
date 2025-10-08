#include<iostream>
#include<vmnchstate.h>
using namespace std;
#include<inventory.h>
class product{
    int id;
string name;
int price ;
int qty;
};
class payment{

};
class inventory{
public:

void reduce()
};
enum vmstate {idle , selecting , awaitpayment , dispensing , off}
class vendingmchn : public inventory
{
vmstate st;
int idosp;
int qty;
void enterselectst(int id,int qty){
product* p=getp(id);
if(p->qty<qty) cout<<"there are only "<<p->qty<< unit available <<endl; 
else{
    idosp=id;
    st=awaitpayment;
}




}
bool acceptpayment(payment* paym){
product* p =getp(idosp);
bool payok=paym->pay(p->price);
if(!payok){
    cout<<"payment failed"<<endl;
    return false;

}
cout<<"payment done"<<endl;
st=dispensing;

}
void dispens(){
    cout<<"dispensing"<<getp(idosp)->getname();
     reduce(idosp,qty); 
     st=idle;
}
 
};
int main(){
 
    return 0;
}