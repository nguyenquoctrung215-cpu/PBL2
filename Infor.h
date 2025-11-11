#ifndef INFOR_H
#define INFOR_H

#include <iostream>
#include <string>
#include "MyVector.h"
using namespace std;

class Infor {
    protected:
        string Id;
        string name;

    public:
        Infor(string Id = "", string name = "");
        
        string getId() const;
        string getName() const;

        virtual void Show() const = 0;
        virtual ~Infor();
};

#endif
