#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "Infor.h"

class Book;
class Reader;
class Borrow;

class Librarian : public Infor {
private:
    string password;
public:
    Librarian(string Id = "", string name = "", string password = "");

    string getPassword() const;
    bool login(const string &inputId, const string &inputPass) const;

    void Show() const override;

    static void LibrarianMenu(MyVector<Book> &books, MyVector<Reader> &readers, MyVector<Borrow> &borrows);
};

#endif
