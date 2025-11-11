#ifndef BOOK_H
#define BOOK_H

#include "Infor.h"

class Borrow;

class Book : public Infor {
private:
    string author;
    int year;
    int total;
    int borrowed;

public:
    Book(string Id = "", string name = "", string author = "", int year = 0, int total = 0, int borrowed = 0);
    void Show() const override;
    static void Show1();
    
    string getAuthor() const;
    int getYear() const;
    int getTotal() const;
    int getAvailable() const;

    static void BorrowBook(MyVector<Book>& books, MyVector<Borrow>& borrows, const string& readerId);
    static void ReturnBook(MyVector<Book>& books, MyVector<Borrow>& borrows, const string& readerId);
    static void Search(const MyVector<Book> &items, const string& type);
    static void ShowAllBook(const MyVector<Book>& books);
    static void docfile(MyVector<Book>& books);
    static void ghifile(MyVector<Book>& books);
};

int Levenshtein(const string& s1, const string& s2);
double score(const string& keyword, const string& bookname);
int min3(int a, int b, int c);

#endif
