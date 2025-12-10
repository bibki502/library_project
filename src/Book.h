#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
    private:
      string title;
      string author;
      int year;
      string isbn;
      bool isAvailable;
      string borrowedBy;
    public:
        Book (const string& t, const string& a, const int y, const string& i);

        string GetTitle() const;
        string GetAuthor() const;
        int GetYear() const;
        string GetIsbn() const;
        bool GetIsAvailable() const;
        string GetBorrowedBy() const;

        void borrowBook(const std::string& userName);
        void returnBook();
        void displayInfo() const;

};

#endif