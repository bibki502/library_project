#include "Library.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Library::Library(string& datFile){
    dataFile=datFile; //сохраняем путь к файлу
    loadFromFile(); //загружаем данные из файла
}

void Library::addBook(const Book& book){
    books.push_back(book);
}

void Library::addUser(const User& user){
    users.push_back(user);
}

void Library::borrowBook(const string& userName, const string& isbn){
    Book* book=findBookByISBN(isbn); //получим указатель на book с данным isbn
    if(book->GetIsAvailable()==false){
        cout<<"This book is borrowed"<<endl;
        return;
    }
    User* user = findUserByName(userName);
    if (user->canBorrowMore() == false) {
        cout << "User cannot borrow more books" << endl;
        return;
    }

    book->borrowBook(userName);
    user->addBook(isbn);
    cout << "The book was borrowed" << endl;
}

void Library::returnBook(const string& isbn){
    Book* book = findBookByISBN(isbn); //получаем указатель на книгу с данным isbn
    string userName = book->GetBorrowedBy(); //узнаем имя пользовтеля, который взял эту книгу
    User* user = findUserByName(userName); //получаем указательна пользователя с таким именем
    book->returnBook();
    cout << "Book returned successfully!" << endl;
}

Book* Library::findBookByISBN(const string& isbn){
    for (int i = 0; i < (int)books.size(); i++) {
        if (books[i].GetIsbn() == isbn) {
            return &books[i]; //возвращает адрес памяти books[i]
        }
    }
    return 0; //если не найдётся такая книга, вернётся ничего-0
}

User* Library::findUserByName(const string& name){
    for(int i=0; i<(int)users.size(); i++){
        if (users[i].GetName()==name){
            return &users[i];
        }
    }
    return 0;
}

void Library::displayAllBooks(){
    for (int i=0; i<(int)books.size();i++){
        books[i].displayInfo();
    }
}

void Library::displayAllUsers(){
    for (int i=0; i<(int)users.size(); i++){
        users[i].displayProfile();
    }
}

void Library::saveToFile() {
    ofstream file(dataFile);

    for (int i = 0; i < (int)books.size(); i++) {
        file<<"BOOK" << endl;
        file << "Title: " << books[i].GetTitle() << endl;
        file << "Author: " << books[i].GetAuthor() << endl;
        file << "Year: " << books[i].GetYear() << endl;
        file << "ISBN: " << books[i].GetIsbn() << endl;
        //file << "Available: " << (books[i].GetIsAvailable() ? "yes" : "no") << endl;
        if (books[i].GetIsAvailable() == true) {
             file<<"Available: yes"<<endl;
            }
            else {
             file<<"Available: no"<<endl;
        }
        file << "BorrowedBy: " << books[i].GetBorrowedBy() << endl;
    }

    file << "\n---USERS---" << endl;

    for (int i = 0; i < (int)users.size(); i++) {
        file << "USER" << endl;
        file << "Name: " << users[i].GetName() << endl;
        file << "UserID: " << users[i].GetUserId() << endl;
        
        vector<string> borrowed = users[i].GetborrowedBooks();
        file << "BorrowedBooks: ";
        for (int j = 0; j < (int)borrowed.size(); j++) {
            file << borrowed[j];
            if (j != borrowed.size() - 1) file << "|";
        }
        file << endl;
        file << "MaxBooks: " << users[i].GetmaxBooksAllowed() << endl;
        file << endl;
    }

    file.close();
}

void Library::loadFromFile() {
    ifstream file(dataFile);

    string line;
    bool readingBooks = true; //флаг - сейчас читаем книги

    while (getline(file, line)) {
        if (line == "---USERS---") {
            readingBooks = false;
            continue;
        }

        if (readingBooks==true && line == "BOOK") {//мы ещё в разделе книг
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
            available = (line.substr(10) == "yes");//если available=true, то считает yes
            getline(file, line);
            borrowedBy = line.substr(11);

            Book book(title, author, year, isbn);
            if (!available) {
                book.borrowBook(borrowedBy);
            }
            books.push_back(book);
            getline(file, line); // пустая строка
        } 
        else if (readingBooks==false && line == "USER") {
            string name, userId;
            int maxBooks;
            vector<string> borrowedBooks;

            getline(file, line);
            name = line.substr(6);
            getline(file, line);
            userId = line.substr(8);
            getline(file, line);
            string borrowedStr = line.substr(15);
            

            vector<string> pieces;  // Сюда сложим isbn
            string currentPiece = "";  // Текущий isbn

            for (int i = 0; i <(int)borrowedStr.size(); i++) {
                char c = borrowedStr[i];  // Берем очередной символ
                
                if (c == '|') {
                    if (!currentPiece.empty()) {
                        pieces.push_back(currentPiece);
                    }
                    currentPiece = "";  // Начинаем новый isbn
                } else {
                    currentPiece += c;
                }
            }

            // Последний isbn
            if (!currentPiece.empty()) {
                pieces.push_back(currentPiece);
            }

            getline(file, line);
            maxBooks = stoi(line.substr(10));

            User user(name, userId);
            for (size_t i = 0; i < borrowedBooks.size(); i++) {
                user.addBook(borrowedBooks[i]);
            }
            users.push_back(user);
            getline(file, line); // пустая строка
        }
    }

    file.close();
}