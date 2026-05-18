#include <iostream>
using namespace std;

class baseClass {
public:
    virtual void perkenalan() final {
        cout << "Hallo saya Function dari base class";
    }
};
