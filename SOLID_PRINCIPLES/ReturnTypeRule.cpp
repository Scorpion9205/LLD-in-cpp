#include<iostream>
using namespace std;


// Return type rule:- 
// Subtype overriden method return type should be either identical or narrower then parent method's return type.
// This is also called as return type covarience.
// c++ enorces this by covarience
class Animal {
  //some common Animal methods
};

class Dog : public Animal {
   //Additional Dog methods specific to Dogs.
};

class Parent {
    public:
      virtual Animal* getAnimal(){
        cout<<"Parent: Returning Animal instance"<<endl;
        return new Animal();
      }
};

class Child: public Parent {
    public:
      Dog* getAnimal() override{
        cout<<"Child: Returnning Dog instance"<<endl;
        return new Dog();
      }
};


class Client : public Parent {
    private:
     Parent * p;
     public:
      Client(Parent *p){
        this->p=p;
      }
      void takeAnimal(){
        p-> getAnimal();
      }

};

int main(){
    Parent * parent = new Parent();
    Child* child = new Child();

    Client * client = new Client(child);
    client->takeAnimal();

    return 0;
}