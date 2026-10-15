#include<iostream>
using namespace std;

// A precondition must be satisfied before a method can  be executed 
// Sub classes can weaken the precondition but cannot strengthen it.


class User {
    public:
    // Precondition : password must be at least 8 characters long
      virtual void setPassword(string password){
        if(password.length()<8){
            throw invalid_argument("Password must be at least 8 characters long!");
        }
        cout<<"Password set successully"<<endl;
      }
};

class AdminUser : public User{
    public:
    // PreCondition : Password must be at least 6 characters
     void setPassword(string password) override{
        if(password.length()<6){
            throw invalid_argument("Password must be at least 6 characters long");
        }
        cout <<"Password set sucessfully"<<endl;
     }
      
};

int main(){
    User* user = new AdminUser();
    user-> setPassword("Admin1"); //Works fine : AdminUser allows shorter passwords

    return 0;
}