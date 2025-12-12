#include "Book.h"
#include <iostream>
using namespace std;

Book::Book(const string& t, const string& a, const int y, const string& i){
    title=t;
    author=a;
    year=y;
    isbn=i;
    isAvailable = true;
    borrowedBy = "";
}

string Book::GetTitle() const{
    return title;
}

string Book::GetAuthor() const{
    return author;
}

int Book::GetYear() const{
    return year;
}

string Book::GetIsbn() const{
    return isbn;
}

bool Book::GetIsAvailable() const{
    return isAvailable;
}

string Book::GetBorrowedBy() const{
    return borrowedBy;
}

void Book::borrowBook(const string& userName){
    isAvailable=false;
    borrowedBy=userName;
}

void Book::returnBook(){
    isAvailable=true;
    borrowedBy="";
}

void Book::displayInfo() const{
    cout<<"Title: "<<title<<endl;
    cout<<"Author: "<<author<<endl;
    cout<<"Year: "<<year<<endl;
    cout<<"ISBN: "<<isbn<<endl;
    if (isAvailable){
        cout<<"Available"<<endl;
    }
    else{
        cout<<"Not available. Borrowed by: "<<borrowedBy<<endl;
    }
    cout<<"-----------"<<endl;
}