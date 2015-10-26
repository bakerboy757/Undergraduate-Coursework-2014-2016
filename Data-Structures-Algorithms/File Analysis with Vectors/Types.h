//header
#ifndef TYPES_H
#define TYPES_H

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

class Types {
    friend ostream& operator<<(ostream& os, const Types& ty);
    friend bool operator==(const Types& t1, const Types& t2);
public:
    //default
    Types();

    //overload
    Types(string);

    //Destructor
    ~Types();
    
    //Accessor Functions
    int getCounter() const;
    int getLocation() const;
    string getStr() const;

    //Setter Functions
    void setCounter(int);
    void setLocation(int);
    void setStr(string);


protected:
    //taking in charcters from file as split up strings
    string str;

    //will hold how many times that char array occurs in vector
    int counter;

    //will hold where in vector it was held
    int location;

};

#endif


