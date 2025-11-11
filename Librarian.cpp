#include "Function.h"
#include "Book.h"
#include "Reader.h"
#include "Borrow.h"

using namespace std;

Librarian::Librarian(string Id, string name, string password)
    : Infor(Id, name), password(password) {}

string Librarian::getPassword() const 
{
    return password;
}

bool Librarian::login(const string &inputId, const string &inputPass) const 
{
    return (Id == inputId && password == inputPass);
}

void Librarian::Show() const 
{
    //Infor::Show();
}

// ================= Librarian Menu =================
void Librarian::LibrarianMenu(MyVector<Book> &books, MyVector<Reader> &readers, MyVector<Borrow> &borrows) 
{
    MyVector<string>menu;
    menu.push_back("Show all books");
    menu.push_back("Show all readers");
    menu.push_back("Show all borrow records");
    menu.push_back("Add new book");
    menu.push_back("Add new reader");
    menu.push_back("Logout and return to main menu");
    
    while (1){
        int choice = hienthimenu(menu,"LIBRARIAN MENU");
        switch (choice) 
        {
            case 0:
                Book::ShowAllBook(books);
                break;

            case 1:
                Reader::ShowAllReader(readers);
                break;

            case 2:
                Borrow::ShowAllBorrow(borrows,readers,books);
                break;

            case 3: 
            {
                string id, name, author;
                int year, total;
                cout << "Enter Book ID: "; getline(cin, id);
                cout << "Enter Book Name: "; getline(cin, name);
                cout << "Enter Author: "; getline(cin, author);
                cout << "Enter Year: "; cin >> year;
                cout << "Enter Total Quantity: "; cin >> total;
                cin.ignore();
                books.push_back(Book(id, name, author, year, total));
                Book::ghifile(books);
                cout << "Book added successfully!\n";
                break;
            }

            case 4: 
            {
                string id, name, address, phone, pass;
                cout << "Enter Reader ID: "; getline(cin, id);
                cout << "Enter Name: "; getline(cin, name);
                cout << "Enter Address: "; getline(cin, address);
                cout << "Enter Phone: "; getline(cin, phone);
                cout << "Enter password (6 digits): "; getline(cin,pass);
                readers.push_back(Reader(id, name, address, phone, pass));
                Reader::ghifile(readers);
                cout << "Reader added successfully!\n";
                break;
            }
            case 5:
                cout << "Logging out librarian...\n";
                return;

            default:
                cout << "Invalid choice!\n";
        }

         cout << "\nPress Enter to continue...";
            cin.get();
    }

}
