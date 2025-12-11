#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;

class User{
    private:
        string name;
        string userId;
        vector<string> borrowedBooks;
        int maxBooksAllowed;
    public:
        User(const string& n, const string& id);
        
        string GetName() const;
        string GetUserId() const;
        vector<string> GetborrowedBooks() const;
        int GetmaxBooksAllowed() const;

        bool canBorrowMore() const;
        void addBook(const string& isbn);
        void removeBook(const string& isbn);
        void displayProfile() const;



};
#endif