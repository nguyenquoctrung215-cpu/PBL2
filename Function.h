#ifndef MENU_H
#define MENU_H
#include "Infor.h"
#include "Librarian.h"
#include "Borrow.h"
#include "Book.h"
#include "Reader.h"
class Funct{
    public:
        static void run();
};
int hienthimenu(const MyVector<string>&, const string&);
string hidenpass(int len = 6);
#endif
