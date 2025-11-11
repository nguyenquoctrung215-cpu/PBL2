#ifndef READER_H
#define READER_H

#include "Infor.h"
#include "Book.h"

class Borrow;
class Reader : public Infor {
private:
    string address;
    string phone;
    string password;

public:
    Reader(string Id = "", string name = "", string address = "", string phone = "", string password = "");

    void Show() const override;
    static void Show1(); 

    string getAddress() const{ return address;}
    string getPhone() const{  return phone;}
    string getPassword() const{ return password;}
    void changePass(MyVector<Reader>& readers);

    bool login(const string &inputId, const string &inputPass) const{
        return (Id == inputId && password == inputPass);
    }
    
    static void docfile(MyVector<Reader>& readers);
    static void ghifile(MyVector<Reader>& readers);
    static void ShowAllReader(const MyVector<Reader>& readers);
    void ReaderMenu(MyVector<Book> &books, MyVector<Borrow> &borrows, MyVector<Reader> &readers);
};


#endif
