#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Book class to represent individual books
class Book {
private:
    string title;
    string author;
    int isbn;
    bool available;

public:
    // Constructor
    Book(const string& title = "", const string& author = "", int isbn = 0, bool available = true)
        : title(title), author(author), isbn(isbn), available(available) {}

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getISBN() const { return isbn; }
    bool isAvailable() const { return available; }

    // Setters
    void setTitle(const string& newTitle) { title = newTitle; }
    void setAuthor(const string& newAuthor) { author = newAuthor; }
    void setAvailable(bool status) { available = status; }

    // Display book information
    void display() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Available: " << (available ? "Yes" : "No") << endl << endl;
    }
};

// Student class to represent individual students
class Student {
private:
    int rollNumber;
    string name;
    double balance;

public:
    // Constructor
    Student(int roll = 0, const string& studentName = "", double initialBalance = 0.0)
        : rollNumber(roll), name(studentName), balance(initialBalance) {}

    // Getters
    int getRollNumber() const { return rollNumber; }
    string getName() const { return name; }
    double getBalance() const { return balance; }

    // Setters
    void setName(const string& newName) { name = newName; }
    void setBalance(double newBalance) { balance = newBalance; }

    // Methods
    void deposit(double amount) {
        balance += amount;
    }

    bool deductAmount(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    void display() const {
        cout << "Roll No: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }
};

// Library Management System class
class LibrarySystem {
private:
    static const int MAX_STUDENTS = 20;
    static const int MAX_BOOKS = 15;
    
    vector<Student> students;
    vector<Book> books;

    // Helper methods
    int findStudentIndex(int rollNumber) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getRollNumber() == rollNumber) {
                return i;
            }
        }
        return -1;
    }

    int findBookIndex(int isbn) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getISBN() == isbn) {
                return i;
            }
        }
        return -1;
    }

    void initializeBooks() {
        // Initialize with sample books
        for (int i = 0; i < MAX_BOOKS; i++) {
            books.push_back(Book("Sample Title " + to_string(i + 1), 
                                "Sample Author " + to_string(i + 1), 
                                1000 + i, 
                                true));
        }
    }

public:
    // Constructor
    LibrarySystem() {
        initializeBooks();
    }

    // Student management methods
    bool createAccount() {
        if (students.size() >= MAX_STUDENTS) {
            cout << "Student limit reached. Cannot create more accounts.\n";
            return false;
        }

        int roll;
        cout << "Enter roll number (BBRRRR format): ";
        cin >> roll;

        if (findStudentIndex(roll) != -1) {
            cout << "Account already exists for this roll number.\n";
            return false;
        }

        string name;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);

        double initialDeposit;
        cout << "Enter initial deposit amount ($50 minimum): ";
        cin >> initialDeposit;

        if (initialDeposit < 50) {
            cout << "Initial deposit must be at least $50.\n";
            return false;
        }

        // Deduct account opening fee ($20) and security deposit ($30)
        double finalBalance = initialDeposit - 20 - 30;
        
        students.push_back(Student(roll, name, finalBalance));
        cout << "Account created successfully!\n";
        return true;
    }

    void displayStudent(int rollNumber) {
        int index = findStudentIndex(rollNumber);
        if (index == -1) {
            cout << "Student not found.\n";
            return;
        }
        students[index].display();
    }

    void depositAmount(int rollNumber, double amount) {
        int index = findStudentIndex(rollNumber);
        if (index == -1) {
            cout << "Student not found.\n";
            return;
        }

        students[index].deposit(amount);
        cout << "New balance: $" << fixed << setprecision(2) 
             << students[index].getBalance() << endl;
    }

    void issueBook(int rollNumber) {
        int studentIndex = findStudentIndex(rollNumber);
        if (studentIndex == -1) {
            cout << "Student not found.\n";
            return;
        }

        cout << "Available books:\n";
        int availableCount = 0;
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].isAvailable()) {
                cout << i + 1 << ". " << books[i].getTitle() 
                     << " by " << books[i].getAuthor() 
                     << " (ISBN: " << books[i].getISBN() << ")\n";
                availableCount++;
            }
        }

        if (availableCount == 0) {
            cout << "No books available.\n";
            return;
        }

        int choice;
        cout << "Enter the number of the book you want to issue (0 to cancel): ";
        cin >> choice;

        if (choice == 0) {
            return;
        }

        if (choice > 0 && choice <= static_cast<int>(books.size()) && 
            books[choice - 1].isAvailable()) {
            
            if (students[studentIndex].deductAmount(2.0)) {
                books[choice - 1].setAvailable(false);
                cout << "Book issued successfully. New balance: $" 
                     << fixed << setprecision(2) 
                     << students[studentIndex].getBalance() << endl;
            } else {
                cout << "Insufficient balance to issue the book.\n";
            }
        } else {
            cout << "Invalid choice or book unavailable.\n";
        }
    }

    void displaySortedStudents() {
        if (students.empty()) {
            cout << "No students enrolled.\n";
            return;
        }

        // Create a copy for sorting
        vector<Student> sortedStudents = students;
        
        // Sort by roll number
        sort(sortedStudents.begin(), sortedStudents.end(), 
             [](const Student& a, const Student& b) {
                 return a.getRollNumber() < b.getRollNumber();
             });

        cout << "Enrolled Students (sorted by roll number):\n";
        for (const auto& student : sortedStudents) {
            cout << student.getRollNumber() << " - " << student.getName() 
                 << " - Balance: $" << fixed << setprecision(2) 
                 << student.getBalance() << endl;
        }
    }

    // Book management methods
    void addBook() {
        if (books.size() >= MAX_BOOKS) {
            cout << "Book limit reached. Cannot add more books.\n";
            return;
        }

        string title, author;
        int isbn;

        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, title);

        cout << "Enter book author: ";
        getline(cin, author);

        cout << "Enter book ISBN: ";
        cin >> isbn;

        if (findBookIndex(isbn) != -1) {
            cout << "A book with this ISBN already exists.\n";
            return;
        }

        books.push_back(Book(title, author, isbn, true));
        cout << "Book added successfully!\n";
    }

    void editBook() {
        int isbn;
        cout << "Enter book ISBN to edit: ";
        cin >> isbn;
        
        int index = findBookIndex(isbn);
        if (index == -1) {
            cout << "Book not found.\n";
            return;
        }

        string newTitle, newAuthor;
        
        cout << "Current book title: " << books[index].getTitle() << endl;
        cout << "Enter new book title: ";
        cin.ignore();
        getline(cin, newTitle);
        books[index].setTitle(newTitle);

        cout << "Current book author: " << books[index].getAuthor() << endl;
        cout << "Enter new book author: ";
        getline(cin, newAuthor);
        books[index].setAuthor(newAuthor);

        cout << "Book details updated successfully!\n";
    }

    void viewBooks() {
        if (books.empty()) {
            cout << "No books in the library.\n";
            return;
        }

        cout << "Library Books:\n";
        for (const auto& book : books) {
            book.display();
        }
    }

    bool studentExists(int rollNumber) {
        return findStudentIndex(rollNumber) != -1;
    }
};

// Authentication class
class AuthSystem {
private:
    string adminPassword;
    string studentPassword;

public:
    AuthSystem() : adminPassword("password"), studentPassword("password") {}

    bool authenticateAdmin(const string& password) {
        return password == adminPassword;
    }

    bool authenticateStudent(const string& password) {
        return password == studentPassword;
    }
};

// Main Application class
class LibraryApp {
private:
    LibrarySystem library;
    AuthSystem auth;

    void showAdminMenu() {
        int option;
        cout << "\nAdmin Menu:\n";
        cout << "1. Add book\n";
        cout << "2. Edit book\n";
        cout << "3. View book status\n";
        cout << "4. View enrolled students\n";
        cout << "5. View student balance\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.editBook();
                break;
            case 3:
                library.viewBooks();
                break;
            case 4:
                library.displaySortedStudents();
                break;
            case 5: {
                int roll;
                cout << "Enter student roll number: ";
                cin >> roll;
                library.displayStudent(roll);
                break;
            }
            default:
                cout << "Invalid option!\n";
        }
    }

    void showStudentMenu(int rollNumber) {
        int option;
        cout << "\nStudent Menu:\n";
        cout << "1. View balance\n";
        cout << "2. Deposit amount\n";
        cout << "3. Issue book\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                library.displayStudent(rollNumber);
                break;
            case 2: {
                double amount;
                cout << "Enter the amount to deposit: ";
                cin >> amount;
                library.depositAmount(rollNumber, amount);
                break;
            }
            case 3:
                library.issueBook(rollNumber);
                break;
            default:
                cout << "Invalid option!\n";
        }
    }

public:
    void run() {
        int option;
        string password;

        while (true) {
            cout << "\n=== Library Management System ===\n";
            cout << "Login as:\n";
            cout << "1. Admin\n";
            cout << "2. Student\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> option;

            if (option == 0) {
                cout << "Thank you for using the Library Management System!\n";
                break;
            }

            cout << "Enter password: ";
            cin >> password;

            if (option == 1) {
                // Admin login
                if (auth.authenticateAdmin(password)) {
                    cout << "Admin login successful!\n";
                    showAdminMenu();
                } else {
                    cout << "Incorrect admin password.\n";
                }
            } else if (option == 2) {
                // Student login
                if (auth.authenticateStudent(password)) {
                    int rollNumber;
                    cout << "Enter your roll number: ";
                    cin >> rollNumber;

                    if (!library.studentExists(rollNumber)) {
                        cout << "Student not found. Create an account? (1. Yes / 2. No): ";
                        int createChoice;
                        cin >> createChoice;
                        if (createChoice == 1) {
                            library.createAccount();
                        }
                    } else {
                        cout << "Student login successful!\n";
                        showStudentMenu(rollNumber);
                    }
                } else {
                    cout << "Incorrect student password.\n";
                }
            } else {
                cout << "Invalid option!\n";
            }
        }
    }
};

int main() {
    LibraryApp app;
    app.run();
    return 0;
}