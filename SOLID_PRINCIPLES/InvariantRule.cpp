// The Invariant Rule is one of the three key rules of the Liskov Substitution Principle (LSP). It says that a subclass must preserve the invariants (the fundamental truths or constraints) established by its base class.

// 🔑 What It Means
// Invariant = A condition that must always hold true for an object’s state.

// If the base class guarantees certain properties, the subclass cannot break them.

// Subclasses can strengthen invariants (add more constraints), but they cannot weaken or violate the parent’s invariants.

#include <iostream>
#include <stdexcept>
using namespace std;

class BankAccount {
protected:
    double balance;

public:
    BankAccount(double initial) {
        if (initial < 0) {
            throw invalid_argument("Balance cannot be negative");
        }
        balance = initial;  // ✅ invariant: balance >= 0
    }

    virtual void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Deposit must be positive");
        }
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            throw invalid_argument("Invalid withdrawal");
        }
        balance -= amount;  // ✅ invariant preserved
    }

    double getBalance() const { return balance; }
};

// ❌ Violates invariant rule
class OverdraftAccount : public BankAccount {
public:
    OverdraftAccount(double initial) : BankAccount(initial) {}

    void withdraw(double amount) override {
        balance -= amount;  // ❌ balance can go negative
    }
};

// ✅ Correct subclass (strengthens invariant)
class SavingsAccount : public BankAccount {
public:
    SavingsAccount(double initial) : BankAccount(initial) {}

    void withdraw(double amount) override {
        if (amount > balance - 100) { // keep minimum balance of 100
            throw invalid_argument("Minimum balance must be preserved");
        }
        balance -= amount;  // ✅ invariant strengthened
    }
};

int main() {
    try {
        BankAccount acc1(500);
        acc1.deposit(200);
        acc1.withdraw(100);
        cout << "BankAccount balance: " << acc1.getBalance() << endl;

        OverdraftAccount acc2(300);
        acc2.withdraw(400);  // ❌ violates invariant
        cout << "OverdraftAccount balance: " << acc2.getBalance() << endl;

        SavingsAccount acc3(1000);
        acc3.withdraw(850);  // ❌ throws exception (minimum balance rule)
        cout << "SavingsAccount balance: " << acc3.getBalance() << endl;

    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
  