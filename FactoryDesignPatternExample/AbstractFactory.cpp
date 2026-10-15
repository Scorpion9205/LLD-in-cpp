#include<iostream>
using namespace std;

class Burger {
    public:
      virtual void prepare() =0; //pure virtual function
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
        cout<<"Preparing Standard Burger..."<<endl;
      }
};

class PremiumBurger : public Burger {
    public:
      void prepare() override {
        cout<<"Preparing Premium Burger...."<<endl;
      }
};

class BasicWheatBurger : public Burger {
    public:
      void prepare() override  {
        cout<<"Preparing Basic Wheat Burger..."<<endl;
      }
};

class StandardWheatBurger : public Burger{
    public:
      void prepare() override {
        cout<<"Preparing Standard Wheat Burger"<<endl;
      }
};

class PremiumWheatBurger : public Burger {
    public:
      void prepare() override {
        cout <<"Preparing Premium Wheat Burger..."<<endl;
      }
};

// Product 2 --> GarlicBread 

class GarlicBread{
    public:
      virtual void prepare() = 0;
};

class BasicGarlicBread : public GarlicBread {
    public:
      void prepare() override {
        cout<<"Preparing Basic Garlic Bread..."<<endl;
      }
};

class CheeseGarlicBread : public GarlicBread{
    public:
      void prepare() override {
        cout<<"Preparing Cheese Garlic Bread..."<<endl;
      }
};

class BasicWheatGarlicBread : public GarlicBread{
    public:
      void prepare() override {
        cout<<"Preparing Basic Wheat Garlic Bread..."<<endl;
    }
};

class CheeseWheatGarlicBread : public GarlicBread {
    public:
      void prepare() override {
        cout<<"Preparing Cheese Wheat Garlic Bread..."<<endl;
      }
};


// Factory and its concretions
class MealFactory {
    public:
      virtual Burger * createBurger(string& type) = 0;
      virtual GarlicBread* createGarlicBread(string & type) = 0;
};

class SinghBurger : public MealFactory {
    public:
      Burger* createBurger(string & type) override {
        if(type == "basic"){
            return new BasicBurger();
        }else if(type=="standard"){
            return new StandardBurger();
        }else if (type == "premium"){
            return new PremiumBurger();
        }else{
            cout<<"Invalid burger type!"<<endl;
            return nullptr;
        }
      }

      GarlicBread * createGarlicBread(string& type) override {
        if(type == "basic"){
            return new BasicGarlicBread();
        }else if (type=="cheese"){
            return new CheeseGarlicBread();
        }else{
            cout<<"Invalid Garlic bread type!"<<endl;
            return nullptr;
        }
      }
};

class KingBurger : public MealFactory{
    public:
      Burger* createBurger(string & type) override {
        if(type == "basic"){
            return new BasicWheatBurger();
        }else if(type == "standard"){
            return new StandardWheatBurger();
        }else if(type=="premium"){
            return new PremiumWheatBurger();
        }else{
            cout<<"Invalid burger type!"<<endl;
            return nullptr;
        }
      }

      GarlicBread* createGarlicBread(string & type) override{
        if(type=="basic"){
            return new BasicWheatGarlicBread();
        }else if(type == "cheese"){
            return new CheeseWheatGarlicBread();
        }else{
            cout<<"Invalid Garlic bread type!"<<endl;
            return nullptr;
        }
      }
};


int main(){
    string burgerType = "standard";
    string garlicBreadType = "cheese";

    MealFactory * mealFactory = new KingBurger();

    Burger* burger = mealFactory->createBurger(burgerType);
    GarlicBread* garlicBread = mealFactory->createGarlicBread(garlicBreadType);

    if(burger) burger->prepare();
    if(garlicBread) garlicBread->prepare();

    delete burger;
    delete garlicBread;
    delete mealFactory;

    return 0;
}
