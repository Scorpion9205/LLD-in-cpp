#include <iostream>
#include <string>
using namespace std;

// Component Interface
class Character {
public:
    virtual string getAbilities() const = 0;
    virtual ~Character() {}
};

// Concrete Component
class Mario : public Character {
public:
    string getAbilities() const override {
        return "Mario";
    }
};

// Abstract Decorator
class CharacterDecorator : public Character {
protected:
    Character* character; // Wrapped component
public:
    CharacterDecorator(Character* c) : character(c) {}
    virtual ~CharacterDecorator() {}
};

// Concrete Decorator: Height-Increasing Powerups
class HeightUp : public CharacterDecorator {
public:
    HeightUp(Character* c) : CharacterDecorator(c) {}
    string getAbilities() const override {
        return character->getAbilities() + " + HeightUp";
    }
};

// Concrete Decorator: Gun Shooting Power-up
class GunPowerUp : public CharacterDecorator {
public:
    GunPowerUp(Character* c) : CharacterDecorator(c) {}
    string getAbilities() const override {
        return character->getAbilities() + " + Gun";
    }
};

// Concrete Decorator: Star Power-Up
class StarPowerUp : public CharacterDecorator {
public:
    StarPowerUp(Character* c) : CharacterDecorator(c) {}
    string getAbilities() const override {
        return character->getAbilities() + " + Star Power (Limited Time)";
    }
    ~StarPowerUp() {
        cout << "Destroying StarPowerUp Decorator" << endl;
    }
};

int main() {
    // Create a basic Mario Character
    Character* mario = new Mario();
    cout << "Basic Character: " << mario->getAbilities() << endl;

    // Decorate Mario with a HeightUp power-up
    mario = new HeightUp(mario);
    cout << "After HeightUp: " << mario->getAbilities() << endl;

    // Add a GunPowerUp
    mario = new GunPowerUp(mario);
    cout << "After GunPowerUp: " << mario->getAbilities() << endl;

    // Finally, add a StarPowerUp decoration
    mario = new StarPowerUp(mario);
    cout << "After StarPowerUp: " << mario->getAbilities() << endl;

    delete mario;
    return 0;
}

