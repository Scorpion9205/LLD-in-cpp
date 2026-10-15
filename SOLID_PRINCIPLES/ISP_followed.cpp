#include<iostream>
using namespace std;

class IPrinter {
    public:
      virtual void print() =0;
      virtual ~IPrinter(){}
};

class IScanner {
    public:
      virtual void scan() =0;
      virtual ~IScanner(){} 
};

class IFax{
    public:
      virtual void fax() =0;
      virtual ~IFax(){}
};

class SimplePrinter : public IPrinter{
    public:
     void print() override{
        cout<<"Printing Document...\n";
     }
};

class MultiFunctionPrinter:public IPrinter,public IScanner,public IFax{
    public:
      void print() override {
        cout<<"Printing document...\n";
      }

      void scan() override {
        cout<<"Scanning document...\n";
      }

      void fax() override{
        cout<<"Sending Fax...\n";
      }
};