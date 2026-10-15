#include <iostream>
using namespace std;

// Abstraction
class IDatabase {
public:
    virtual void saveData(const string& data) = 0;
    virtual ~IDatabase() {}
};

// Low-level implementations
class MySQLDatabase : public IDatabase {
public:
    void saveData(const string& data) override {
        cout << "Saving '" << data << "' to MySQL\n";
    }
};

class PostgresDatabase : public IDatabase {
public:
    void saveData(const string& data) override {
        cout << "Saving '" << data << "' to Postgres\n";
    }
};

// High-level module depends on abstraction
class OrderService {
    IDatabase* db;
public:
    OrderService(IDatabase* database) : db(database) {}
    void placeOrder(const string& order) {
        db->saveData(order);
    }
};

int main() {
    MySQLDatabase mysql;
    PostgresDatabase postgres;

    OrderService orderService1(&mysql);
    orderService1.placeOrder("Order#123");

    OrderService orderService2(&postgres);
    orderService2.placeOrder("Order#456");
}
