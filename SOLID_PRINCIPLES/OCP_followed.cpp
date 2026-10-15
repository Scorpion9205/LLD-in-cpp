#include<iostream>
#include<vector>

using namespace std;

// product class representing any item 
class Product{
    public:
    string name;
    double price;

    Product(string name,double price){
        this->name = name;
        this->price = price;
    }
};

// 1.) Shopping Cart : Only responsible for cart related business logic
class ShoppingCart{
    private:
      vector<Product*>products;
    public:
      void addProducts(Product *p){
        products.push_back(p);
      }

      const vector<Product*>getProducts(){
        return products;
      }

      double calculateTotal(){
        double total = 0.0;
        for(auto p : products){
            total +=p->price;
        }
        return total;
      }
};


// 2. ShoppingCartPrinter : Only responsible for printing invoices
class ShoppingCartPrinter {
    private:
      ShoppingCart* cart;
    public:
      ShoppingCartPrinter(ShoppingCart* cart){
        this-> cart = cart;
      }

      void printInvoice(){
        cout<<"Shopping Cart Invoice:\n";
        for(auto p:cart->getProducts()){
            cout << p->name <<" - $"<<p->price<<endl;

        }
        cout<<"Total : $"<<cart->calculateTotal()<<endl;
      }
};

//Abstract class
class Persistence{
    private:
      ShoppingCart*cart;
    public:
      virtual void save(ShoppingCart * cart) =0; //pure virtual function
};

class SQLPersistence : public Persistence{
    public:
     void save(ShoppingCart* cart) override {
        cout<<"Saving Shopping cart to SQL DB.."<<endl;
     }
};

class MongoPersistence:public Persistence {
    public:
     void save(ShoppingCart* cart) override {
        cout<<"Saving shopping cart to MongoDB..."<<endl;
     }
};

class FilePersistence : public Persistence {
    public:
     void save(ShoppingCart * cart ) override {
        cout<<"Saving shopping cart to a file..."<<endl;
     }
};

int main(){
    ShoppingCart* cart = new ShoppingCart();
    cart->addProducts(new Product("Laptop",1000));
    cart->addProducts(new Product("Mouse",100));

    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();
    Persistence* db = new SQLPersistence();
    Persistence* mongo = new MongoPersistence();
    Persistence* file = new FilePersistence();

    db->save(cart);
    mongo->save(cart);
    file->save(cart);

    return 0;
}