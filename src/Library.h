#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <vector>
#include <string>
using namespace std;

class Library{
    private:
        vector<Book> books; //каталог книг
        vector<User> users; //список зарегестрированных пользователей
        string dataFile; //путь к файлу с сохранёнными данными
    public:
        Library(string& datFile);
        void addBook(const Book& book);
        void addUser(const User& user);
        void borrowBook(const string& userName, const string& isbn);
        void returnBook(const string& isbn);
        Book* findBookByISBN(const string& isbn);
        User* findUserByName(const string& name);
        void displayAllBooks();
        void displayAllUsers();
        void saveToFile();
        void loadFromFile();

};

#endif