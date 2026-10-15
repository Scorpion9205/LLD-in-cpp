#include<iostream>
using namespace std;

/*

class Singleton {
    public:
      Singleton (){
        cout<<"Singleton Constructor called. New Object created."<<endl;
      }
};

*/

/*
int main(){
    Singleton * s1 = new Singleton(); // object 1
    Singleton * s2 = new Singleton(); // object 2

    cout<<(s1==s2)<<endl; // prints 0 because alag alag jagah object bane heap me jo barabar ho hi nhi sakte 
}
    */ 

// abhi tak singleton ke constructor kai bar call ho rhe hai aur nye nye object ban rhe hai agar ise rok le to singleton pattern follow ho jayega (new jkeyword use na kar paye)

/*

class Singleton {
    private:  // public-> private kardo
    // par isse ek dikkat hai ki ek bhi object nhi ban payega par hame ek object to bnana padega 
    static Singleton* instance;   // static pointer to single instance
      Singleton (){
        cout<<"Singleton Constructor called. New Object created."<<endl;
      }

      public:
      static Singleton* getInstance() {
        if(instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }


};

Singleton* Singleton::instance = nullptr;z
int main(){
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    if(s1 == s2) {
        cout << "Both are the same instance!" << endl;
    }
}


*/

// making class Thread safe 
// Critical Section vo section hota hai jo multiple threads ek sath execute kar sakta hai 
// introducing locks to create it thread safe 

class Singleton {
    private: 
    static Singleton* instance; 
    static mutex mtx;  
      Singleton (){
        cout<<"Singleton Constructor called. New Object created."<<endl;
      }

      public:
      static Singleton* getInstance() {
        lock_guard<mutex> lock(mtx);  // Lock for thread safety
        if(instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    // upar wale locking ko avoid karna chahiye jitna ho sake ab dusra tarika ye bhi pura accha nhi h 
/*
    if(instance == nullptr) {
     // agar t1 and t2 do thread ek sath access karenge  to problem hogi 
        lock_guard<mutex> lock(mtx);
        instance = new Singleton();
    }
  isko thik karne ke liye double locking use karenge
    */

    // if(instance == nullptr){
    //     lock_guard<mutex> lock(mtx);
    //     if(instance == nullptr){
    //         instance = new Singleton();

    //     }
    };


// initialize static members
Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;
int main(){
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    if(s1 == s2) {
        cout << "Both are the same instance!" << endl;
    }
}


// ye sab kuch karne ki jarurat nhi hai locking aur double locking in dono ka fix hai eager initialization 




// Real world uses of singleton class 
// 1.) logging system
// 2.) Databse Connection
// 3.) Configuration Manager