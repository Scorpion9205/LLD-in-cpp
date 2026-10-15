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

// 3.ShoppingCartStorage : only responsible for saving cart to DB
// but it is breaking open close principle 
class ShoppingCartStorage {
    private:
     ShoppingCart *cart;
    public:
    ShoppingCartStorage(ShoppingCart * cart){
        this->cart = cart;
    }
    void saveToSQLDatabase(){
        cout<<"Saving shopping cart to SQL DB..."<<endl;
    }
    void saveToMongoDatabase(){
        cout<<"Saving shopping cart to Mongo DB;"<<endl;
    }

    void saveToFile(){
        cout<<"Saving shopping cart to File..."<<endl;
    }
};

int main(){
    ShoppingCart * cart = new ShoppingCart();

    cart ->addProducts(new Product("Laptop",1500));
    cart ->addProducts(new Product("Mouse",50));

    ShoppingCartPrinter * printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    ShoppingCartStorage* db = new ShoppingCartStorage(cart);
    db->saveToSQLDatabase();
    db->saveToFile();
    return 0;

}