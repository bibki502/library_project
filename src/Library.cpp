#include "Library.h"
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

// 10. СОХРАНИТЬ В ФАЙЛ
void Library::saveToFile(){
    // Пока просто сообщение
    cout << "Saving data to: " << dataFile << endl;
    cout << "(File save not implemented yet)" << endl;
}

// 11. ЗАГРУЗИТЬ ИЗ ФАЙЛА
void Library::loadFromFile() {
    // Пока просто сообщение
    cout << "Loading data from: " << dataFile << endl;
    cout << "(File load not implemented yet)" << endl;
    cout << "Starting with empty library." << endl;
}