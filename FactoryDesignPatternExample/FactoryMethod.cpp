#include<iostream>
#include<string>

using namespace std;

class Burger {
    public:
      virtual void prepare() = 0; // pure virtual function
      virtual ~Burger(){} // Virtual destructor
};

class BasicBurger : public Burger {
    public:
      void prepare() override {
        cout << "Preparing Basic Burger"<<endl;
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

class BasicWheatBurger : public Burger {
    public:
      void prepare() override  {
        cout<<"preparing basic wheat burger...";
      }
};

class StandardWheatBurger : public Burger{
    public:
      void prepare() override {
        cout<<"Preparing Standard wheat burger";
      }
};

class PremiumWheatBurger : public Burger {
    public:
      void prepare() override {
        cout <<"Preparing Premium Wheat Burger...";
      }
};

// Factory and its concretions 
class BurgerFactory {
    public:
      virtual Burger* createBurger(const string& type) = 0;
      virtual ~BurgerFactory() {}
};

class SinghBurger : public BurgerFactory {
    public:
      Burger* createBurger(const string& type) override{
        if(type == "basic"){
            return new BasicBurger();
        }else if(type=="standard"){
            return new StandardBurger();
        }else if(type=="premium"){
            return new PremiumBurger();
        }else{
            cout<<"Invalid burger type!"<<endl;
            return nullptr;
        }
      }
};

class KingBurger : public BurgerFactory {
    public:
      Burger* createBurger(const string& type) override{
        if(type == "basic"){
            return new BasicWheatBurger();
        }else if(type=="standard"){
            return new StandardWheatBurger();
        }else if(type=="premium"){
            return new PremiumWheatBurger();
        }else{
            cout<<"Invalid burger type!"<<endl;
            return nullptr;
        }
      }
};

int main(){
    string type = "basic";

    BurgerFactory* myFactory = new KingBurger();

    Burger* burger = myFactory->createBurger(type);

    if(burger == nullptr){
        cout<<"Failed to create burger."<<endl;
        return 1;
    }

    burger->prepare();
    return 0;
}