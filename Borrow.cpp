#include "Borrow.h"
#include "Reader.h"
#include "Book.h"
#include <sstream>
#include <fstream>
#include <iomanip>

Borrow::Borrow(string readerId, string bookId, int book)
    : readerId(readerId), bookId(bookId), borrowId(readerId + bookId), bookborrowed(book) {}

string Borrow::getBorrowId() const { return borrowId; }
string Borrow::getReaderId() const { return readerId; }
string Borrow::getBookId() const { return bookId; }
int Borrow::getBook() const { return bookborrowed;}
void Borrow::addqty(int x){ bookborrowed += x;}

void Borrow::Show1(){
    cout << left << setw(10) << "No" << setw(20) << "ID" << setw(25) << "Reader" << setw(20) << "Book" 
         << setw(10) << "Quantity" << endl;
    cout << string(83, '-') << endl;
}

void Borrow::Show(const MyVector<Reader>& readers, const MyVector<Book>& books) const 
{
    string name, book;
    for (int i = 0; i < readers.length(); i++)
        if (readers[i].getId() == readerId){
            name = readers[i].getName();
            break;
        }

    for (int i = 0; i < books.length(); i++)
        if (books[i].getId() == bookId){
            book = books[i].getName();
            break;
        }

    cout << left << setw(20) << borrowId << setw(25) << name << setw(21) << book 
         << right << setw(7) << bookborrowed << endl;
}

void Borrow::ShowAllBorrow(MyVector<Borrow> &borrows, MyVector<Reader>& readers,  MyVector<Book>& books) 
{
    if (borrows.empty()){
        cout << "No borrow records!\n";
        return;
    }

    cout << right << setw(70) << "=============== BORROW LIST =================\n\n";
    Show1();
    cout << endl;
    for (int i = 0; i < borrows.length(); i++){
        cout << left << setw(10) << i+1;
        borrows[i].Show(readers,books);
    }
}

void Borrow::docfile(MyVector<Borrow>& borrows){
    string line;
    ifstream borrowfile("borrows.txt");
        if (!borrowfile){
            cout << "Borrowfile not found!\n";
            return;
        }
        while (getline(borrowfile,line)){
            string readerid, bookid, temp;
            int book;
            stringstream ss(line);
            getline(ss, readerid, '|');
            getline(ss, bookid, '|');
            getline(ss, temp, '|');
            book = stoi(temp);

            borrows.push_back(Borrow(readerid, bookid, book));
        }
        borrowfile.close();
}

void Borrow::ghifile(MyVector<Borrow>& borrows){
    ofstream borrowfile("borrows.txt");
        for (int i = 0; i < borrows.length(); i++){
            Borrow& bo = borrows[i];
            borrowfile << bo.getReaderId() << "|" << bo.getBookId() << "|" << bo.getBook() << endl;
        }
        borrowfile.close();
}
void Borrow::ShowBorrowByReader(MyVector<Borrow> &borrows, MyVector<Reader> &readers, MyVector<Book> &books, const string& currentId) 
{
    bool found = false;
    int no = 1;

    for (int i = 0; i < borrows.length(); i++) 
    {
        Borrow& b = borrows[i];
        if (b.getReaderId() == currentId) 
        {
            if (!found){
                cout <<  right << setw(70) << "=============== BORROW RECORD =================\n\n";
                Show1();
                found = true;
            }
            cout << left << setw(10) << no++;
            b.Show(readers, books);
        }
    }

    if (!found)
        cout << "This reader has no borrow records.\n";
}
