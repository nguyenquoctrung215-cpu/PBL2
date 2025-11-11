#include "Book.h"
#include "Borrow.h"
#include <fstream>
#include <sstream>
#include <utility>
#include <iomanip>

Book::Book(string Id, string name, string author, int year, int total, int borrowed)
    : Infor(Id, name), author(author), year(year), total(total), borrowed(borrowed) {}

void Book::Show() const 
{   
    cout << left << setw(10) << Id << setw(25) << name << setw(20) << author << setw(8)  << year
         << right << setw(5)  << total << setw(11) << borrowed << setw(11) << total - borrowed << endl;
}

void Book::Show1(){
    cout << left << setw(5) << "No" << setw(10) << "ID" << setw(25) << "Name" << setw(20) << "Author" << setw(8) << "Year"
                 << setw(8) << "Total" << setw(10) << "Borrowed" << setw(10) << "Available" << endl;
    cout << string(95,'-') << endl;
}

int min3(int a, int b, int c){
    int min = (a < b) ? a : b;
    return (min < c) ? min : c;
}

int Levenshtein(const string& s1, const string& s2){
    int m = s1.length(), n = s2.length();
    MyVector<int> pre(n+1), cur(n+1);

    for (int i = 0; i <= n; i++) pre[i] = i;

    for (int i = 1; i <= m; i++){
        cur[0] = i;
        for (int j = 1; j <= n; j++){
            if (s1[i-1] == s2[j-1])
                cur[j] = pre[j-1];
            else
                cur[j] = min3(pre[j-1]+1, pre[j] +1, cur[j-1]+1);
        }
        pre = cur;
    }
    return pre[n];
}

double score(const string& keyword, const string& bookname){
    MyVector<string> keys, words;
    string s, key = keyword, name = bookname;
    double totalscore = 0;
    int count = 0;
    for (auto &c : key) c = tolower(c);
    for (auto &c : name) c = tolower(c);

    stringstream s1(key), s2(name);
    while (s1 >> s) keys.push_back(s);
    while (s2 >> s) words.push_back(s);

    for (int i = 0; i < keys.length(); i++)
        for (int j = 0; j < words.length(); j++){
            int dis = Levenshtein(keys[i], words[j]);
            int maxlen = max(keys[i].length(), words[j].length());
            double sc = 1.0 - (double) dis / maxlen;

            if (words[j].length() >= keys[i].length() && words[j].substr(0, keys[i].length()) == keys[i])
                sc += 0.2;
            
            if (sc > 0.1){
                totalscore += sc;
                count++;
            }
        }
    if (count == 0) return 0;
    return totalscore/count;
}

void Book::Search(const MyVector<Book> &items, const string& type){
    string keyword;
    cout << "Enter keyword: ";
    getline(cin,  keyword);

    if (items.empty()) {
        cout << "No data available!\n";
        return;
    }

    MyVector<pair<double,const Book*>> results;

    for (int i = 0; i <items.length(); i++){
        string value;
        const Book& t = items[i];
        if (type == "name") value = t.getName(); 
            else if (type == "author") value = t.getAuthor();
            else if (type == "id") value = t.getId();

        double s = score(keyword,value);
        if (s >= 0.4) 
            results.push_back({s,&t});
    }

    if (!results.length()){
        cout << "\nNot found!\n";
        return;
    }

    for (int i = 0; i < results.length(); i++)
        for (int j = i+1; j < results.length(); j++)
            if (results[j].first > results[i].first){
                auto temp = results[i];
                results[i] = results[j];
                results[j] = temp;
            }

    cout << endl;
    cout << right << setw(68) << "============= SEARCH RESULT ===============\n\n" ;
    Show1();
    for (int i = 0; i < results.length(); i++){
         cout << left << setw(5) << i+1;
            results[i].second->Show();
        }
}

string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
int Book::getTotal() const { return total; }
int Book::getAvailable() const { return total - borrowed; }

void Book::docfile(MyVector<Book>& books){

    ifstream bookfile("books.txt");
        if (!bookfile){
            cout << "Bookfile not found!\n";
            return;
        }

        string line;
        while (getline(bookfile,line)){

            string id,name,author;
            int year,total, borrowed;

            stringstream ss(line);
            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, author, '|');
            string temp;
            getline(ss, temp, '|'); year = stoi(temp);
            getline(ss, temp, '|'); total = stoi(temp);
            getline(ss,temp); borrowed = stoi(temp);
            books.push_back(Book(id,name,author,year,total, borrowed));
        }
        bookfile.close();
}

void Book::ghifile(MyVector<Book>& books){
    ofstream bookfile("books.txt");
        for (int i = 0; i < books.length(); i++){
            Book& b = books[i];
            bookfile << b.getId() << "|" << b.getName() << "|" << b.getAuthor() << "|" << b.getYear() << "|" << b.getTotal() << "|" << b.borrowed << endl;
        }
        bookfile.close();
}

void Book::BorrowBook(MyVector<Book> &books, MyVector<Borrow> &borrows, const string &readerId)
{
    string bookName; int quantity, total = 0;
    for (int i = 0; i < borrows.length(); i++)
        if (readerId == borrows[i].getReaderId()) total += borrows[i].getBook();

    if (total >= 5){
        cout << "You borrowed 5 books. Please return some before borrowing more!\n";
        return;
    }

    cout << "Enter book name to borrow: ";
    getline(cin, bookName);

    bool found = false;

    for (int i = 0; i < books.length(); i++)
    {
        Book& b = books[i];
        if (b.getName() == bookName)
        {
            found = true;

            cout << "Enter quantity book to borrow: ";
            cin >> quantity;
            cin.ignore();

            if (quantity <= 0){
                cout << "Invalid quantity!\n";
                return;
            }

            if (total + quantity > 5){
                cout << "You can only borrow up to 5 books in total!\n";
                return;
            }

            int allowedbook = 5 - total;
            int avai = b.getAvailable();
            int maxbook = (allowedbook < avai) ? allowedbook : avai; 

            if (quantity > maxbook){
                cout << "You can only borrow up to " << maxbook << " books!\n";
                return;
            }
                string borrowId = readerId + b.getId();
                bool exit = false;

                for (int j = 0; j < borrows.length(); j++){
                    if (borrowId == borrows[j].getBorrowId()){
                        borrows[j].addqty(quantity);
                        exit = true;
                        break;
                    }
                }

                if (!exit)
                    borrows.push_back(Borrow(readerId, b.getId(), quantity));
                b.borrowed += quantity;
                cout << "Borrow success! Borrow ID = " << readerId + b.getId() << endl;
                ghifile(books);
                Borrow::ghifile(borrows);
                break; 
            }
        }
        if (!found)
            cout << "Book not found: " << bookName << endl;
}

void Book::ReturnBook(MyVector<Book> &books, MyVector<Borrow> &borrows, const string &readerId)
{
    string bookName; int returnbook;
    cout << "Enter book name to return: ";
    getline(cin, bookName);

    bool foundBook = false;   
    bool returned = false;   

    for (int i = 0; i < books.length(); i++)
    {
        Book& b = books[i];
        if (b.getName() == bookName)
        {
            foundBook = true;
            string targetId = readerId + b.getId();

            for (int j = 0; j < borrows.length(); j++)
            {
                if (borrows[j].getBorrowId() == targetId)
                {
                    cout << "Enter quantity book to return: ";
                    cin >> returnbook;
                    cin.ignore();

                    if (returnbook <= 0){
                        cout << "Invalid quantity!\n";
                        return;
                    } 

                    if (returnbook > borrows[j].getBook()){
                        cout << "You are returning more books than borrowed!\n";
                        return;
                    }

                    if (returnbook == borrows[j].getBook()) borrows.erase(j);
                    else borrows[j].addqty(-returnbook);
                    
                    b.borrowed -= returnbook;
                    returned = true;
                    ghifile(books);
                    Borrow::ghifile(borrows);
                    break;
                }
            }

            if (!returned)
                cout << "No borrow record found for this book or reader.\n";

            break; 
        }
    }

    if (!foundBook)
        cout << "Book not found: " << bookName << endl;
}


void Book::ShowAllBook(const MyVector<Book> &books) 
{   
    if (books.empty()) 
    {
        cout << "No books available!\n";
        return;
    } else {
        cout << endl;
        cout << right << setw(68) << "=============== BOOK LIST =================\n\n";
        Show1();
        for (int i = 0; i < books.length(); i++){        
            cout << left << setw(5) << i+1;
            books[i].Show();
    }
}
}
