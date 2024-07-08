#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable;

    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isAvailable(true) {}
};

struct Borrower {
    string name;
    unordered_map<string, time_t> borrowedBooks; // ISBN -> due date

    Borrower(string n) : name(n) {}
};

class Library {
private:
    vector<Book> books;
    unordered_map<string, Borrower> borrowers;
    const int finePerDay = 1; // Fine per day for overdue books

    time_t getCurrentTime() {
        return time(0);
    }

    string timeToString(time_t t) {
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &t);
        return string(buffer);
    }

public:
    void addBook(const string& title, const string& author, const string& ISBN) {
        books.push_back(Book(title, author, ISBN));
        cout << "Book added: " << title << " by " << author << " (ISBN: " << ISBN << ")" << endl;
    }

    void searchBook(const string& query) {
        for (const auto& book : books) {
            if (book.title.find(query) != string::npos || book.author.find(query) != string::npos || book.ISBN.find(query) != string::npos) {
                cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.ISBN << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
            }
        }
    }

    void checkoutBook(const string& borrowerName, const string& ISBN) {
        for (auto& book : books) {
            if (book.ISBN == ISBN && book.isAvailable) {
                book.isAvailable = false;
                time_t dueDate = getCurrentTime() + (7 * 24 * 60 * 60); // Due in one week
                if (borrowers.find(borrowerName) == borrowers.end()) {
                    borrowers[borrowerName] = Borrower(borrowerName);
                }
                borrowers[borrowerName].borrowedBooks[ISBN] = dueDate;
                cout << "Book checked out to " << borrowerName << ". Due date: " << timeToString(dueDate);
                return;
            }
        }
        cout << "Book not available or not found." << endl;
    }

    void returnBook(const string& borrowerName, const string& ISBN) {
        if (borrowers.find(borrowerName) == borrowers.end() || borrowers[borrowerName].borrowedBooks.find(ISBN) == borrowers[borrowerName].borrowedBooks.end()) {
            cout << "No record of this book being borrowed by " << borrowerName << "." << endl;
            return;
        }

        time_t dueDate = borrowers[borrowerName].borrowedBooks[ISBN];
        time_t returnDate = getCurrentTime();
        double diffInSeconds = difftime(returnDate, dueDate);
        int daysOverdue = diffInSeconds / (60 * 60 * 24);

        if (daysOverdue > 0) {
            cout << "Book is " << daysOverdue << " days overdue. Fine: $" << daysOverdue * finePerDay << endl;
        } else {
            cout << "Book returned on time." << endl;
        }

        for (auto& book : books) {
            if (book.ISBN == ISBN) {
                book.isAvailable = true;
                break;
            }
        }
        borrowers[borrowerName].borrowedBooks.erase(ISBN);
    }

    void displayMenu() {
        cout << "\nLibrary Management System Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Checkout Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
    }
};

int main() {
    Library library;
    int choice;
    string title, author, ISBN, borrowerName;

    while (true) {
        library.displayMenu();
        cin >> choice;
        cin.ignore(); // To ignore the newline character after the integer input

        switch (choice) {
        case 1:
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            cout << "Enter book ISBN: ";
            getline(cin, ISBN);
            library.addBook(title, author, ISBN);
            break;
        case 2:
            cout << "Enter title, author, or ISBN to search: ";
            getline(cin, title);
            library.searchBook(title);
            break;
        case 3:
            cout << "Enter borrower's name: ";
            getline(cin, borrowerName);
            cout << "Enter book ISBN: ";
            getline(cin, ISBN);
            library.checkoutBook(borrowerName, ISBN);
            break;
        case 4:
            cout << "Enter borrower's name: ";
            getline(cin, borrowerName);
            cout << "Enter book ISBN: ";
            getline(cin, ISBN);
            library.returnBook(borrowerName, ISBN);
            break;
        case 5:
            cout << "Exiting the program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
