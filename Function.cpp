#include "Function.h"
#include <conio.h>

string hidenpass(int len){
    string pass;
    char c;
    while(1){
        c = getch();
        if (c == 13) break;
        else if (c == 8 && !pass.empty()){
            cout << "\b \b";
            pass.pop_back();
        } else if (c >= 33 && c <= 126){
                if(pass.size() < len){
                    cout << "*";
                    pass += c;
                }
            }
        }
    return pass;
}

int hienthimenu(const MyVector<string>& menu, const string& menutitile)
{
    int pos = 0;
    char key;
    int prev_pos = -1;

    cout << "\033[?25l"; // an con tro
    cout << "\033[2J\033[H"; // xoa man hinh + move con tro len vi tri (1,1) : tieu de menu

    cout << "========" << menutitile << "========\n";
    for (int i = 0; i < menu.length(); i++){
        cout << "  " << menu[i] << "\n";
    }

    while(1){
        // Cập nhật chỉ dòng thay đổi
        if (prev_pos != pos) {
            if (prev_pos != -1) {
                // Reset dòng cũ
                cout << "\033[" << (prev_pos + 2) << "H";
                cout << "\033[0m"; // RESET màu
                cout << "  " << menu[prev_pos];
                cout << "\033[K"; // Xóa đến cuối dòng
            }
            
            // Highlight dòng mới
            cout << "\033[" << (pos + 2) << "H";
            cout << "\033[32m" << ">> " << menu[pos] << " <<";
        }

        key = getch();

        if (key == 72){ // up
            prev_pos = pos;
            pos = (pos == 0) ? menu.length()-1 : pos-1;
        } else if (key == 80){ // down
            prev_pos = pos;
            pos = (pos == menu.length()-1) ? 0 : pos+1;
        } else if (key == 13){ // enter
            cout << "\033[?25h"; // hiện con trỏ
            cout << "\033[0m"; // reset màu
            cout << "\033[2J\033[H"; // dọn màn hình
            return pos;
        }
    }
}
    void Funct::run(){

        MyVector<Book> books; Book::docfile(books);
        MyVector<Reader> readers; Reader::docfile(readers);
        MyVector<Borrow> borrows; Borrow::docfile(borrows);

        MyVector<Librarian> librarians;
        librarians.push_back(Librarian("admin1", "Thu Thu A", "123456"));
        librarians.push_back(Librarian("admin2", "Thu Thu B", "678910"));

        MyVector <string> mainmenu;
        mainmenu.push_back("Login as Reader");
        mainmenu.push_back("Login as Librarian");
        mainmenu.push_back("Search book by name");
        mainmenu.push_back("Show all books");
        mainmenu.push_back("Exit");

    while (1){
        int choice = hienthimenu(mainmenu, "MAIN MENU");
        switch (choice) {
            case 0: { // Login Reader
                string id, pass;
                int attemp = 0;
                bool loggedIn = false;
                cout << "Enter Reader ID: ";
                getline(cin, id);
                do{
                    cout << "Enter Password: ";
                    pass = hidenpass();
                    for (int i = 0; i < readers.length(); i++){
                        if (readers[i].login(id, pass)){
                            cout << "\nLogin success! Welcome, " << readers[i].getName() << endl;
                            cin.get();
                            readers[i].ReaderMenu(books, borrows, readers);
                            loggedIn = true;
                            break;
                        }
                    }

                    if (!loggedIn){
                        attemp++;
                        if (attemp < 3){
                            cout << "\nInvalid ID or password! Please try again(" << (3-attemp) << " attemps left)!\n";
                            cin.get();
                            cout << "\033[2H\033[J"; // H: di chuyen, J: xoa het
                        }
                            else {
                                cout << "\nToo many failed attemps. Returning to main menu\n";
                                cin.get();
                                break;
                            }
                    }
                } while (!loggedIn && attemp < 3);
                break;
        }

            case 1: { // Login Librarian
                string id, pass;
                char c, x[7];
                int i = 0;
                cout << "Enter Librarian ID: ";
                getline(cin, id);
                cout << "Enter Password: ";
                pass = hidenpass();

                bool loggedIn = false;
                for (int i = 0; i < librarians.length(); i++){
                    if (librarians[i].login(id, pass)){
                        cout << "\nLogin success! Welcome, " << librarians[i].getName() << endl;
                        cin.get();
                        Librarian::LibrarianMenu(books, readers, borrows);
                        loggedIn = true;
                        break;
                    }
                }

                if (!loggedIn){
                    cout << "\nInvalid ID or password!\n";
                    cin.get();
                }
                    break;
            }

            case 2: 
            { 
                Book::Search(books, "name");
                cout << "\nPress Enter to continue...";
                cin.get();
                break;
            }

            case 3: 
                Book::ShowAllBook(books);
                cout << "\nPress Enter to continue...";
                cin.get();
                break;

            case 4:
                cout << "Exiting program...\n";
                cin.get();
                return;

            default:
                cout << "Invalid choice! Please try again.\n";
                cout << "\nPress Enter to continue...";
                cin.get();
                break;
        }
    }
    }


