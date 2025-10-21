#include <sstream>

#include "book.h"

using namespace std;

// Default constructor
Book::Book() : title(""), author(""), isbn(""), isAvailable(true), borrowerName("") {}

// Parameterized constructor
Book::Book(const string& title, const string& author, const string& isbn)
    : title(title), author(author), isbn(isbn), isAvailable(true), borrowerName("") {}

// Getters
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getISBN() const { return isbn; }
bool Book::getAvailability() const { return isAvailable; }
string Book::getBorrowerName() const { return borrowerName; }

// Setters
void Book::setTitle(const string& title) { this->title = title; }
void Book::setAuthor(const string& author) { this->author = author; }
void Book::setISBN(const string& isbn) { this->isbn = isbn; }
void Book::setAvailability(bool available) { this->isAvailable = available; }
void Book::setBorrowerName(const string& name) { this->borrowerName = name; }

// Check out the book
void Book::checkOut(const string& borrower) {
    isAvailable = false;
    borrowerName = borrower;
}

// Return the book
void Book::returnBook() {
    isAvailable = true;
    borrowerName.clear();
}

// Human-readable representation
string Book::toString() const {
    string result = "Titre: " + title + "\nAuteur: " + author + "\nISBN: " + isbn +
                    "\nDisponible: " + (isAvailable ? "Oui" : "Non");
    if (!isAvailable && !borrowerName.empty()) {
        result += "\nEmprunté par: " + borrowerName;
    }
    return result;
}

// File storage format: title|author|isbn|1|borrowerName
string Book::toFileFormat() const {
    string availability = isAvailable ? "1" : "0";
    string result = title + "|" + author + "|" + isbn + "|" + availability + "|" + borrowerName;
    return result;
}

// Parse from file format
void Book::fromFileFormat(const string& line) {
    stringstream ss(line);
    string token;

    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, isbn, '|');

    string availStr;
    getline(ss, availStr, '|');
    isAvailable = (availStr == "1");

    // Read remaining field (borrowerName). If absent, borrowerName becomes empty.
    getline(ss, borrowerName, '|');
    // If the parsed availability indicates available, ensure borrowerName is empty.
    if (isAvailable) {
        borrowerName.clear();
    }
}