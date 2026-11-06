#include<iostream>
#include<string>

using namespace std;

// Implementation Hierarchy : Engine interface (Abstraction)
class Engine{
    public:
    virtual void start() = 0;
    virtual ~Engine() = default;
};

// Concrete Implementors
class PetrolEngine : public Engine{
    public:
      void start() override {
        cout << "Petrol Engine Started" << endl;
      }
};

class DieselEngine : public Engine{
    public:
      void start() override {
        cout << "Diesel Engine Roaring to life" <<endl;
      }
};

class ElectricEngine : public Engine{
    void start() override {
        cout<<"Electric Engine whiring up"<<endl;
    }
};

// Abstraction Hierarchy : car
class Car{
    protected:
    Engine* engine;
    public:
     Car(Engine* eng):engine(eng){}
     virtual void drive() =0;
};

// Refined Abstraction : sedan
class Sedan:public Car{
    public:
    Sedan(Engine* eng):Car(eng){}
    void drive()override{
        engine->start();
        cout<<"Driving a Sedan on the highway."<<endl;
    }
};

// Refined Abstraction : SUV
class SUV:public Car{
    public:
      SUV(Engine* eng):Car(eng){}
      void drive()override{
        engine->start();
        cout<<"Driving an SUV off-road."<<endl;
      }
};

int main(){
    // Create Engine implementations on the heap
    Engine* petrolEngine = new PetrolEngine();
    Engine* dieselEngine = new DieselEngine();
    Engine* electricEngine = new ElectricEngine();

    // Create Car abstractions,injecting Engine implementations
    Car* mySedan = new Sedan(petrolEngine);
    Car* mySUV = new SUV(electricEngine);
    Car* yourSUV = new SUV(dieselEngine);

    // Use the cars
    mySedan->drive();
    mySUV->drive();
    yourSUV->drive();

    // clean up
    delete mySedan;
    delete mySUV;
    delete yourSUV;

    return 0;

}