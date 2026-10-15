#include<iostream>
#include<vector>
using namespace std;

// product class represents the product details of the shopping cart
class Product{
    public:
        string name;
        double price;
        Product(string name,double price){
            this->name =name;
            this->price = price;
        }
};

// Voilating SRP: ShoppingCart is handling multiple responsibilities
class ShoppingCart{
    private:
      vector<Product*> products;

    public:
      void addProduct(Product* product){
        products.push_back(product);
      }

      const vector<Product*>& getProducts() const{
        return products;
      }

      //1. SRP: Voilared: calculate total price in cart
      double calculateTotal(){
        double total = 0.0;
        for(const Product* product : products){
            total += product->price;
        }
        return total;
      }

      // Voilating SRP: Prints invoice (should be handled by Invoice class)
      void printInvoice(){
        cout<<"Shopping Cart Invoice:"<<endl;
        for(const Product* product : products){
            cout<<product->name<<" - $"<<product->price<<endl;
        }
        cout<<"Total: $"<<calculateTotal()<<endl;
      }

      void saveToDatabase(){
        cout<<"Saving shopping cart to database..."<<endl;
      }

};

int main(){
    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Laptop",1000.0));
    cart->addProduct(new Product("Mouse",20.0));
    cart->printInvoice();
    cart->saveToDatabase();
    return 0;
}