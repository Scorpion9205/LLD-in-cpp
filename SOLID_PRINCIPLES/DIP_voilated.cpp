// Definition: High‑level modules should not depend on low‑level modules. Both should depend on abstractions.

// Goal: Prevent tight coupling, make systems flexible and testable.

// Benefit: You can swap implementations (e.g., database, logger, payment gateway) without changing the business logic.

#include <iostream>
using namespace std;

class MySQLDatabase {
public:
    void saveData(const string& data) {
        cout << "Saving '" << data << "' to MySQL\n";
    }
};

class OrderService {
    MySQLDatabase db;  // Direct dependency on concrete class
public:
    void placeOrder(const string& order) {
        db.saveData(order);  // tightly coupled
    }
};
