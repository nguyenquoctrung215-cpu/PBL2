#include "Reader.h"
#include "Function.h"
#include "Borrow.h"
#include <iomanip>
#include <fstream>

Reader::Reader(string Id, string name, string address, string phone, string pass)
    : Infor(Id, name), address(address), phone(phone), password(pass) {}

void Reader::Show() const 
{
    cout << left << setw(10) << Id << setw(25) << name << setw(20) << address
                 << setw(12) << phone << endl;
}
void Reader::Show1(){
    cout << left << setw(5) << "No" << setw(10) << "ID" << setw(25) << "Name"
                 << setw(20) << "Address" << setw(12) << "Phone" << endl;
    cout << string(70,'-') << endl;
}

void Reader::changePass(MyVector<Reader>& readers){
    string curpas, newpas, pas;

    cout << "Enter you current password: ";
    curpas = hidenpass();

    if (curpas != password){
        cout << "\nIncorrect password!";
        return;
    }

    cout << "\nEnter your new password: ";
    newpas = hidenpass();
    cout << "\nConfirm you new password: ";
    pas = hidenpass();

    if (newpas != pas){
        cout << "\nInvalid!\n";
        return;
    } else {
            password = pas;
            cout << "\nChange successfully!\n";
            ghifile(readers);
        }
}

void Reader::docfile(MyVector<Reader>& readers){
    string line;
    ifstream readerfile("readers.txt");
        if (!readerfile){
            cout << "Readerfile not found!\n";
            return;
        }
        while (getline(readerfile,line)){

            string id,name,address,phone,pass;

            stringstream ss(line);
            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, address, '|');
            getline(ss, phone, '|');
            getline(ss,pass, '|');
            readers.push_back(Reader(id,name,address,phone,pass));
        }
        readerfile.close();
}

void Reader::ghifile(MyVector<Reader>& readers){
    ofstream readerfile("readers.txt");
        for (int i = 0; i < readers.length(); i++){
            Reader& r = readers[i];
            readerfile << r.getId() << "|" << r.getName() << "|" << r.getAddress() << "|" << r.getPhone()  << "|" << r.getPassword() << endl;
        }
        readerfile.close();
}

void Reader::ShowAllReader(const MyVector<Reader>& readers) 
{
    if (readers.empty()) {
        cout << "No readers available!\n";
        return;
    } else {
        cout << endl;
        cout << right << setw(55) << "============= READER LIST ===============\n\n";
        Show1();
        for (int i = 0; i < readers.length(); i++) {
             cout << left << setw(5) << i+1;
            readers[i].Show();
        }
    }
}
void Reader::ReaderMenu(MyVector<Book> &books, MyVector<Borrow> &borrows, MyVector<Reader> &readers) 
{   
    MyVector <string> menu;
    menu.push_back("Change your password");
    menu.push_back("Search book by name");
    menu.push_back("Search book by author");
    menu.push_back("Show all books");
    menu.push_back("Borrow books");
    menu.push_back("Return books");
    menu.push_back("Show your borrow records");
    menu.push_back("Logout and return to main menu");

    while(1){
        int choice = hienthimenu(menu, "READER MENU");
        switch (choice) 
        {
            case 0:
                changePass(readers);
                cin.ignore();
                break;

            case 1: 
            {
                Book::Search(books, "name");
                break;
            }
            case 2:
            {
                Book::Search(books, "author");
                break;
            }
            case 3:
                Book::ShowAllBook(books);
                break;
            case 4:
                Book::BorrowBook(books, borrows, getId());
                break;
            case 5:
                Book::ReturnBook(books, borrows, getId());
                break;
            case 6:
                Borrow::ShowBorrowByReader(borrows, readers, books, getId());
                break;
            case 7:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice!\n";
        }
            cout << "\nPress Enter to continue...";
            cin.get();
    }
}
