#include "Library.h"
#include <iostream>
   string fileName = "test.txt";
    Library lib(fileName);
#include <iostream>
#include "Library.h"

using namespace std;

void showMenu() {
    cout << "\n=== LIBRARY ===" << endl;
    cout << "1. Show all books" << endl;
    cout << "2. Show all users" << endl;
    cout << "3. Add new book" << endl;
    cout << "4. Register new user" << endl;
    cout << "5. Borrow a book" << endl;
    cout << "6. Return a book" << endl;
    cout << "7. Search book by ISBN" << endl;
    cout << "8. Show user profile" << endl;
    cout << "9. Save data to file" << endl;
    cout << "10. Exit" << endl;
    cout << "Enter your choice (1-10): ";
}

int main() {

    string fileName = "data_library.txt";
    Library lib(fileName);
    
    int choice = 0;
    
    while (choice != 10) {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "\n--- ALL BOOKS ---" << endl;
                lib.displayAllBooks();
                break;
                
            case 2: 
                cout << "\n--- ALL USERS ---" << endl;
                lib.displayAllUsers();
                break;
                
            case 3: 
            {
                cout << "\n--- ADD BOOK ---" << endl;
                
                string title, author, isbn;
                int year;
                
                cout << "Title: ";
                getline(cin, title);
                
                cout << "Author: ";
                getline(cin, author);
                
                cout << "Year: ";
                cin >> year;
                
                cout << "ISBN: ";
                getline(cin, isbn);
                
                Book newBook(title, author, year, isbn);
                lib.addBook(newBook);
                
                cout << "Book added" << endl;
                break;
            }
                
            case 4:
            {
                cout << "\n--- REGISTER NEW USER ---" << endl;
                
                string name, userId;
                
                cout << "Name: ";
                getline(cin, name);
                
                cout << "ID (format: USR_001): ";
                getline(cin, userId);
                
                User newUser(name, userId);
                lib.addUser(newUser);
                
                cout << "User registered" << endl;
                break;
            }
                
            case 5:
            {
                cout << "\n--- BORROW A BOOK ---" << endl;
                
                string userName, isbn;
                
                cout << "Name: ";
                getline(cin, userName);
                
                cout << "ISBN of book: ";
                getline(cin, isbn);
                
                lib.borrowBook(userName, isbn);
                cout << "Book borrowed" << endl;
            }
                
            case 6:
            {
                cout << "\n--- RETURN A BOOK ---" << endl;
                
                string isbn;
                
                cout << "ISBN of book to return: ";
                getline(cin, isbn);
                
                lib.returnBook(isbn);
                cout << "Book returned successfully!" << endl;
            }
                
            case 7:
            {
                cout << "\n--- FIND BOOK BY ISBN ---" << endl;
                
                string isbn;
                cout << "ISBN to search: ";
                getline(cin, isbn);
                
                Book* foundBook = lib.findBookByISBN(isbn);
                
                if (foundBook != nullptr) {
                    cout << "\nBook found:" << endl;
                    foundBook->displayInfo();
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            }
                
            case 8:
            {
                cout << "\n--- SHOW USER PROFILE ---" << endl;
                
                string userName;
                cout << "Name: ";
                getline(cin, userName);
                
                User* foundUser = lib.findUserByName(userName);
                
                if (foundUser != nullptr) {
                    cout << "\nUser profile:" << endl;
                    foundUser->displayProfile();
                } else {
                    cout << "User not found." << endl;
                }
                break;
            }
                
            case 9:
                cout << "\n--- SAVE DATA ---" << endl;
                lib.saveToFile();
                cout << "Data saved to file" << endl;
                
            case 10:
                cout << "\nExit" << endl;
                lib.saveToFile();
                break;
                
            default:
                cout << "Enter a number from 1 to 10." << endl;
                break;
        }
    }
    
    return 0;
}