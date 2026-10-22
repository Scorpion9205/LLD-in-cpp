#include <iostream>
using namespace std;

class Beverage {
public:
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

protected:
    void boilWater() {
        cout << "Boiling water\n";
    }

    void pourInCup() {
        cout << "Pouring into cup\n";
    }

    virtual void brew() = 0;
    virtual void addCondiments() = 0;
};

class Tea : public Beverage {
    protected:
        void brew() override {
            cout << "Steeping tea leaves\n";
        }
    
        void addCondiments() override {
            cout << "Adding lemon\n";
        }
    };

class Coffee : public Beverage {
        protected:
            void brew() override {
                cout << "Brewing coffee\n";
            }
        
            void addCondiments() override {
                cout << "Adding sugar and milk\n";
            }
};

int main() {
    Tea tea;
    Coffee coffee;

    cout << "Making Tea:\n";
    tea.prepareRecipe();

    cout << "\nMaking Coffee:\n";
    coffee.prepareRecipe();

    return 0;
}
