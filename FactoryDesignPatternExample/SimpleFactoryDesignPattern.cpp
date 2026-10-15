// A single factory class decides which object to create based on input.

// Example: ShapeFactory returning Circle or Square.
#include<iostream>

using namespace std;

class Burger{
    public:
      virtual void prepare() =0; // pure virtual function
      virtual ~Burger() {} //Virtual destructor
};

class BasicBurger : public Burger{
    public:
      void prepare() override{
        cout<<"Preparing Basic Burger with bun, patty and ketchup"<<endl;
      }
};

class StandardBurger : public Burger {
    public:
      void prepare() override {
        cout<<"Preparing Standard Burger...";
      }
};

class PremiumBurger : public Burger {
    public:
      void prepare() override {
        cout<<"Preparing Premium Burger....";
      }
};

class BurgerFactory{
    public:
      Burger* createBurger(string & type){
        if(type == "basic"){
            return new BasicBurger();
        }else if(type == "standard"){
            return new StandardBurger();
        }else if(type == "premium"){
            return new PremiumBurger();
        }else {
            cout<<"Invalid burger type!"<<endl;
            return nullptr;
        }
      }
};

int main() {
    string type = "standard";
    BurgerFactory * myBurgerFactory = new BurgerFactory();
    Burger * burger = myBurgerFactory->createBurger(type);
    burger->prepare();
    return 0;
}