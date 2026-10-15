#include<iostream>
using namespace std;

// Here I machine is a fat interface which containd more than one abstract method 
class IMachine {
    public:
      virtual void print()=0;
      virtual void scan() =0;
      virtual void fax() =0;
      virtual ~IMachine() {}
};

// ISP voilates : simple printer should not have the ability to scan 
class SimplePrinter : public IMachine{
    public:
      void print() override{
        cout<<"Printing document...\n";
      }
      void scan() override {
        // not supported
        cout<<"Scan not supported!\n";
      }

      void fax(){
        // not supported
        cout<<"Fax not supported!\n";
      }

};
