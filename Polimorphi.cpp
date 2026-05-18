#include <iostream>
using namespace std;

class baseClass {
public:
    virtual void perkenalan() {
        cout << "Hallo saya Function dari base class" << endl;
    }
};

class derivedClass : public baseClass {
public:
    void perkenalan() override {
        cout << "Hallo saya Function dari derived Class" << endl;
    }
};

int main() {
    baseClass* basePtr;
    derivedClass derivedObj;

    basePtr = &derivedObj;

    basePtr->perkenalan();

    return 0;
}