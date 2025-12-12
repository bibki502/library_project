#include "Library.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

Library::Library(const string& datFile) {  // Исправлено на const string&
    dataFile = datFile;
    loadFromFile();
}

void Library::addBook(const Book& book){
    books.push_back(book);
}

void Library::addUser(const User& user){
    users.push_back(user);
}

void Library::borrowBook(const string& userName, const string& isbn){
    Book* book = findBookByISBN(isbn);
    if (!book) {
        cout << "Book not found!" << endl;
        return;
    }
    
    if(!book->GetIsAvailable()){
        cout<<"This book is borrowed"<<endl;
        return;
    }
    
    User* user = findUserByName(userName);
    if (!user) {
        cout << "User not found!" << endl;
        return;
    }
    
    if (user->canBorrowMore() == false) {
        cout << "User cannot borrow more books" << endl;
        return;
    }

    book->borrowBook(userName);
    user->addBook(isbn);
    cout << "The book was borrowed" << endl;
}

void Library::returnBook(const string& isbn){
    Book* book = findBookByISBN(isbn);
    if (!book) {
        cout << "Book not found!" << endl;
        return;
    }
    
    string userName = book->GetBorrowedBy();
    User* user = findUserByName(userName);
    
    book->returnBook();
    if (user) {
        user->removeBook(isbn);
    }
    cout << "Book returned" << endl;
}

Book* Library::findBookByISBN(const string& isbn){
    for (int i = 0; i < (int)books.size(); i++) {
        if (books[i].GetIsbn() == isbn) {
            return &books[i];
        }
    }
    return nullptr;  // Лучше возвращать nullptr
}

User* Library::findUserByName(const string& name){
    for(int i = 0; i < (int)users.size(); i++){
        if (users[i].GetName() == name){
            return &users[i];
        }
    }
    return nullptr;  // Лучше возвращать nullptr
}

void Library::displayAllBooks(){
    if (books.empty()) {
        cout << "No books in library" << endl;
        return;
    }
    for (int i = 0; i < (int)books.size(); i++){
        books[i].displayInfo();
    }
}

void Library::displayAllUsers(){
    if (users.empty()) {
        cout << "No registered users" << endl;
        return;
    }
    for (int i = 0; i < (int)users.size(); i++){
        users[i].displayProfile();
    }
}

void Library::saveToFile() {
    ofstream file(dataFile);
    if (!file.is_open()) {
        cout << "Cannot open file for writing!" << endl;
        return;
    }

    for (int i = 0; i < (int)books.size(); i++) {
        file << "BOOK" << endl;
        file << "Title: " << books[i].GetTitle() << endl;
        file << "Author: " << books[i].GetAuthor() << endl;
        file << "Year: " << books[i].GetYear() << endl;
        file << "ISBN: " << books[i].GetIsbn() << endl;
        
        if (books[i].GetIsAvailable() == true) {
            file << "Available: yes" << endl;
        } else {
            file << "Available: no" << endl;
        }
        
        file << "BorrowedBy: " << books[i].GetBorrowedBy() << endl;
        file << endl;  // Пустая строка между книгами
    }

    file << "---USERS---" << endl;

    for (int i = 0; i < (int)users.size(); i++) {
        file << "USER" << endl;
        file << "Name: " << users[i].GetName() << endl;
        file << "UserID: " << users[i].GetUserId() << endl;
        
        vector<string> borrowed = users[i].GetborrowedBooks();
        file << "Borrowed Books: ";
        for (int j = 0; j < (int)borrowed.size(); j++) {
            file << borrowed[j];
            if (j != borrowed.size() - 1) file << "|";
        }
        file << endl;
        file << "MaxBooks: " << users[i].GetmaxBooksAllowed() << endl;
        file << endl;  // Пустая строка между пользователями
    }

    file.close();
}

void Library::loadFromFile() {
    ifstream file(dataFile);
    if (!file.is_open()) {
        cout << "File not found. Starting with empty library." << endl;
        return;
    }

    books.clear();  // Очищаем текущие данные
    users.clear();

    string line;
    bool readingBooks = true;

    while (getline(file, line)) {
        if (line == "---USERS---") {
            readingBooks = false;
            continue;
        }

        if (readingBooks && line == "BOOK") {
            string title, author, isbn, borrowedBy;
            int year;
            bool available;

            getline(file, line);
            title = line.substr(7);
            getline(file, line);
            author = line.substr(8);
            getline(file, line);
            year = stoi(line.substr(6));
            getline(file, line);
            isbn = line.substr(6);
            getline(file, line);
            available = (line.substr(10) == "yes");
            getline(file, line);
            borrowedBy = line.substr(11);

            Book book(title, author, year, isbn);
            if (!available) {
                book.borrowBook(borrowedBy);
            }
            books.push_back(book);
            getline(file, line); // Пропускаем пустую строку
        } 
        else if (!readingBooks && line == "USER") {
            string name, userId;
            int maxBooks;
            vector<string> borrowedBooks;

            getline(file, line);
            name = line.substr(6);
            getline(file, line);
            userId = line.substr(8);
            getline(file, line);
            string borrowedStr = line.substr(11);
            
            // Разбиваем строку на ISBN
            vector<string> pieces;
            string currentPiece = "";

            for (int i = 0; i < (int)borrowedStr.size(); i++) {
                char c = borrowedStr[i];
                
                if (c == '|') {
                    if (!currentPiece.empty()) {
                        pieces.push_back(currentPiece);
                    }
                    currentPiece = "";
                } else {
                    currentPiece += c;
                }
            }

            // Последний ISBN
            if (!currentPiece.empty()) {
                pieces.push_back(currentPiece);
            }

            getline(file, line);
            maxBooks = stoi(line.substr(10));

            User user(name, userId);
            // Исправлено: используем pieces вместо borrowedBooks
            for (size_t i = 0; i < pieces.size(); i++) {
                user.addBook(pieces[i]);
            }
            users.push_back(user);
            getline(file, line); // Пропускаем пустую строку
        }
    }

    file.close();
}