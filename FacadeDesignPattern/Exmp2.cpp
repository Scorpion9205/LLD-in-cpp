#include <iostream>
using namespace std;

// Subsystem 1
class DVDPlayer {
public:
    void on() {
        cout << "DVD Player ON" << endl;
    }

    void play() {
        cout << "Playing Movie..." << endl;
    }
};

// Subsystem 2
class Projector {
public:
    void on() {
        cout << "Projector ON" << endl;
    }
};

// Subsystem 3
class SoundSystem {
public:
    void on() {
        cout << "Sound System ON" << endl;
    }
};

// Facade
class HomeTheaterFacade {
private:
    DVDPlayer dvd;
    Projector projector;
    SoundSystem sound;

public:
    void watchMovie() {
        cout << "Starting Home Theater..." << endl;

        dvd.on();
        projector.on();
        sound.on();
        dvd.play();
    }
};

int main() {
    HomeTheaterFacade theater;

    // Client only talks to Facade
    theater.watchMovie();

    return 0;
}