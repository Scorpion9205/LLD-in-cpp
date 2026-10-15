#include<iostream>
using namespace std;



//Method Argument rule:
// Subtype method arguments can be identical or wider than the super
// c++ imposes this by keeping signature identical

class Parent {
    public:
     virtual void print(string msg){
        cout<<"Parent: "<<msg <<endl;
     }
};

class Child : public Parent {
    public:
     void print(string msg) override {
        cout<<"Child: "<<msg<<endl;
     }
};

// client that pass string as msg as client expects
class Client{
    private:
      Parent *p;
    public:
    Client(Parent * p){
        this->p = p;
    }
    void printmsg(){
        p->print("Hello");
    }
};

int main(){
    Parent* parent = new Parent();
    Parent* child = new Child();

    //Client* client = new Client(parent);
    Client* client = new Client(child);
    client->printMsg();
}