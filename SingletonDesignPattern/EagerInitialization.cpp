#include<iostream>
#include<mutex>

using namespace std;

class Singleton {
    private:
      static Singleton* instance;

      Singleton(){
        cout<<"Singleton Constructor Called!"<<endl;
      }
    public:
      static Singleton* getInstance(){
        return instance;
      }

};

//Initialize static members
Singleton* Singleton::instance = new Singleton();

int main(){
    Singleton * s1 = Singleton::getInstance();
    Singleton * s2 = Singleton::getInstance();

    cout<<(s1 == s2)<<endl;
}

// Eager initialization utna use nhi kiya jata kyuki aisa ho sakte hai hamne pehle se object banke rakh liya par vo kahi use hi nhi hua iska matlab memory loss ho jayegi sari jo hai 