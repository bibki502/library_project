#include "User.h"
#include<iostream>
#include <string>
#include <vector>

User::User(const string& n, const string& id){
    name=n;
    userId=id;
    maxBooksAllowed=3;
}

string User::GetName() const{
    return name;
}

string User::GetUserId() const{
    return userId;
}

vector<string> User::GetborrowedBooks() const{
    return borrowedBooks;
}

int User::GetmaxBooksAllowed() const{
    return maxBooksAllowed;
}

bool User::canBorrowMore() const{
     if (borrowedBooks.size()<maxBooksAllowed){
            return true;
     }
     else {
            return false;
     }
}

void User::addBook(const string& isbn) {
    borrowedBooks.push_back(isbn);
}

void User::removeBook(const string& isbn) {
    for (int i=0; i<(int)borrowedBooks.size(); i++){
        if (borrowedBooks[i]==isbn){
            borrowedBooks.erase(borrowedBooks.begin()+i);
            return;
        }
    }
}

void User::displayProfile() const{
    cout<<"Name: "<<name<<endl;
    cout<<"UserId: "<<userId<<endl;
    cout<<"Max books: "<<maxBooksAllowed<<endl;
    if (!borrowedBooks.empty()) {
        cout << "Borrowed books (ISBN):" <<endl;
        for (int i=0; i<(int)borrowedBooks.size(); i++) {
            cout << "  - " <<borrowedBooks[i]<<endl;
        }
    }
    else {
        cout<<"You didn't borrow books"<<endl;
    }

    cout << "===================" <<endl;
}