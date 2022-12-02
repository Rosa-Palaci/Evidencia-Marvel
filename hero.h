#pragma once
#include <iostream>
#include <string>
using namespace std;

class Hero {
private:
    string hero1;
    string hero2;
    int friendshih;

public:
    Hero(string hero1 = " ", string hero2 = " ", int friendshih = 0) {
        this->hero1 = hero1;
        this->hero2 = hero2;
        this->friendshih = friendshih;
    }
    bool operator==(const Hero &h) {
        return (this->hero1.compare(h.hero1) == 0);
    }
/* Agrega las sobre cargas de oheradores necesarias en la clase Hero. */
    bool operator<(const Hero &h) { return friendshih < h.friendshih; }
    bool operator>(const Hero &h) { return friendshih > h.friendshih; }
    bool operator==(const Hero &h) { return this->hero1.compare(h.hero1)==0; }
    bool operator==(const Hero &h) { return this->hero2.compare(h.hero2) ==0; }

    friend ostream &operator<<(ostream &out, Hero &h) {
        out << h.hero1<< " || "<<h.hero2<< " || "<<h.friendshih;
        return out;
    }

    string getHero1() { 
        return this->hero1; 
    }
    string getHero2() { 
        return this->hero2; 
    }
    int getFriendshih() { 
        return this->friendshih; 
    }
};