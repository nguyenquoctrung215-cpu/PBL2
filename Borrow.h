#ifndef BORROW_H
#define BORROW_H

#include "Infor.h"

class Reader;
class Book;

class Borrow {
private:
    string borrowId; // readerId + bookId
    string readerId;
    string bookId;
    int bookborrowed;

public:
    Borrow(string readerId = "", string bookId = "", int book = 0);

    string getBorrowId() const;
    string getReaderId() const;
    string getBookId() const;
    int getBook() const;
    void addqty(int);
    //void setqty(int);

    void Show(const MyVector<Reader>& readers, const MyVector<Book>& books) const;
    static void Show1();

    static void docfile(MyVector<Borrow>& borrows);
    static void ghifile(MyVector<Borrow>& borrows);
    static void ShowAllBorrow(MyVector<Borrow> &borrows, MyVector<Reader>& readers,  MyVector<Book>& books);
    static void ShowBorrowByReader(MyVector<Borrow> &borrows, MyVector<Reader> &readers, MyVector<Book> &books, const string& currentId);
};

#endif
