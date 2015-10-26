#include "Types.h"


ostream& operator<<(ostream& os, const Types& ty) {
    os << ty.str;
    return os;
}

bool operator==(const Types& t1, const Types& t2) {
    return t1.str == t2.str;
}

//default
Types::Types() {
    str = "";
    counter = 1;
    location = 0;
}

//overload
Types::Types(string s) {
    str = s;
    counter = 1;
    location = 0;
}

//Destructor
Types::~Types() {

}

//Accessor Functions
int Types :: getCounter() const {
    return counter;

}

int Types::getLocation() const {
    return location;
}

string Types::getStr() const {
    return str;
}

//Setter Functions
void Types::setCounter(int count) {
    counter = count;
}

void Types::setLocation(int loc) {
    location = loc;
}

void Types::setStr(string s){
    str = s;
}
