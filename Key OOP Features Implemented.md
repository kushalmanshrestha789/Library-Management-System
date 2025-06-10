Key OOP Features Implemented:
1. Classes Created:

Book - Encapsulates book data and behaviors
Student - Manages student information and account operations
LibrarySystem - Core library management functionality
AuthSystem - Handles authentication logic
LibraryApp - Main application controller

2. Encapsulation:

Private data members with public getter/setter methods
Protected internal helper methods
Clear separation of concerns between classes

3. Key Improvements:

Memory Management: Used vector<> instead of fixed arrays for dynamic sizing
String Handling: Replaced C-style strings with std::string
Code Organization: Separated functionality into logical classes
Better Error Handling: More robust input validation
Maintainability: Easier to extend and modify individual components

4. Class Responsibilities:

Book: Manages individual book properties and display
Student: Handles student data and account operations (deposit, deduct)
LibrarySystem: Manages collections of books and students, handles business logic
AuthSystem: Centralized authentication management
LibraryApp: User interface and application flow control

5. Benefits of This OOP Design:

Modularity: Each class has a single responsibility
Reusability: Classes can be easily reused or extended
Maintainability: Changes to one class don't affect others
Scalability: Easy to add new features (like different user types, book categories, etc.)
Data Protection: Private members prevent unauthorized access
