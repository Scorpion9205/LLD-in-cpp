#include<iostream>

using namespace std;

// A PostCondition must be satisied after a method is executed.
// Sub classes can strengthen the PostCondition but cannot weaken it.

class Car{
    protected:
       int speed;

    public:
      Car(){
        speed =0;
      }

      void accelerate(){
        cout<<"Accelerating"<<endl;
        speed +=20;
      }

      // postcondition : speed must reduce after brake
      virtual void brake(){
        cout<<"Applying brakes"<<endl;
      }

};

class HybridCar :public Car {
    private:
      int charge;
    public:
      HybridCar() : Car(){
        charge =0;
      }
      //postCondition : speed must reduce after brake
      // postcondition : charge must increase.

      void brake(){
        cout<<"Applying brakes"<<endl;
        speed -= 20;
        charge +=10;
      }
};

int main(){
    Car* hybridCar = new HybridCar();
    hybridCar->brake(); // works fine : HybridCar reduces speed and also increase charge.
    // Client feels no difference in substituting Hybrid car in place of Car.
}