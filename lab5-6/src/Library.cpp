#include "Library.h"
#include <iostream>  // вывод сообщений
#include <fstream>  // работа с файлами
#include <sstream>  // для разделения строки на части ы
#include <stdexcept>  // исключения

// Конструктор принимает путь к файлу и загружает данные
Library::Library(const std::string& file)
    : dataFile(file) // сохраняеет путь 
    {
        loadFromFile(); //загружает и файла
    }

    void Library::loadFromFile(){
        std::ifstream fin(dataFile); // открываем файл 
        // если файла нет, создадим пустой
        if(!fin.is_open()){
            std::ofstream create(dataFile);
            create << "---USERS---\n"; // разделитель
            create.close();
            std::cout <<"Файл не найден. Создан новый: " << dataFile << "\n";
            return;
        }

        // очищаем данные
        books.clear();
        users.clear();
        // читаем книги
        std::string line;
        while(std::getline(fin,line)){
            if (line == "---USERS---") break; // дошли до секции пользователей 

            if(line == "BOOK"){
                std::string title, author, isbn, borrowedBy;
                int year;
                bool available;
            // читаем каждое поле книги
            std::getline(fin, line);
            title = line.substr(7);        // заголовок

            std::getline(fin, line);
            author = line.substr(8);       // автор

            std::getline(fin, line);
            year = std::stoi(line.substr(6)); // год

            std::getline(fin, line);
            isbn = line.substr(6);         // ИСБН

            std::getline(fin, line);
            available = (line.substr(10) == "yes"); // да/нет

            std::getline(fin, line);
            borrowedBy = line.substr(12);  // фамилия пользователя
            // создаем объект книги
            try {
                Book b(title, author, year, isbn);

                // книга в файле могла быть выдана
                b.setAvailable(available);
                b.setBorrowedBy(borrowedBy);

                books.push_back(b);
            }
            catch (...) {
                std::cout << "Ошибка чтения книги: " << isbn << "\n";
            }
        }
    }
    // чтение пользователей
        while (std::getline(fin, line)) {

            if (line == "USER") {

            std::string name, userId, borrowedLine;
            int maxBooks;

            std::getline(fin, line);
            name = line.substr(6);     // фамилия 

            std::getline(fin, line);
            userId = line.substr(8);   // айди пользователя

            std::getline(fin, line);
            borrowedLine = line.substr(15); // список ИСБН

            std::getline(fin, line);
            maxBooks = std::stoi(line.substr(10)); // максимум        
            // создаемпользователя и восстанавливаем список книг 
            try {
                User u(name, userId);
                u.setMaxBooks(maxBooks);

                std::vector<std::string> list;
                std::stringstream ss(borrowedLine);
                std::string token;

                // Разделяем строку 
                while (std::getline(ss, token, '|')) {
                    if (!token.empty())
                        list.push_back(token);
                }

                u.setBorrowedBooks(list);
                users.push_back(u);
            }
            catch (...) {
                std::cout << "Ошибка чтения пользователя: " << name << "\n";
            }
        }
    }

    fin.close();
}

    void Library::addBook(const Book& book){
        books.push_back(book); //добавляем книгу в каталог
    }
    
    void Library::addUser(const User& user){
        users.push_back(user); //добавляем в список пользователя
    }
 
    Book* Library::findBookByISBN(const std::string& isbn) {
    for (auto& b : books) {
        if (b.getISBN() == isbn)
            return &b; // возвращаем указатель на найденную книгу
    }
    return nullptr; // книга не найдена
}

    User* Library::findUserByName(const std::string& name) {
    for (auto& u : users) {
        if (u.getName() == name)
            return &u; // возвращаем указатель
    }
    return nullptr;
}
    // выдача книги
    void Library::borrowBook(const std::string& userName, const std::string& isbn) {
    // ищем книгу по методу в массиве
    Book* b = findBookByISBN(isbn);
    if (!b) throw std::runtime_error("Книга не найдена.");
    // ищем пользователя по фамилии
    User* u = findUserByName(userName);
    if (!u) throw std::runtime_error("Пользователь не найден.");

    if (!b->getAvailable())
        throw std::runtime_error("Книга уже выдана.");

    if (!u->canBorrowMore())
        throw std::runtime_error("Пользователь достиг лимита по книгам.");

    b->borrowBook(userName);
    u->addBook(isbn);
}
    // возврат книги
    void Library::returnBook(const std::string& isbn) {
    // ищем книгу
    Book* b = findBookByISBN(isbn);
    if (!b) throw std::runtime_error("Книга не найдена.");

    if (b->getAvailable())
        throw std::runtime_error("Книга уже находится в библиотеке.");

    std::string userName = b->getBorrowedBy();
    // ищем пользователя
    User* u = findUserByName(userName);
    if (!u) throw std::runtime_error("Пользователь не найден.");

    b->returnBook();
    u->removeBook(isbn);
}
    // Вывод книг и пользователей
    void Library::displayAllBooks() const {
    for (const auto& b : books)
        b.displayInfo();
}

    void Library::displayAllUsers() const {
    for (const auto& u : users)
        u.displayProfile();
}
    // сохранение данных в файл
    void Library::saveToFile() const {

    std::ofstream fout(dataFile);
    if (!fout.is_open())
        throw std::runtime_error("Не удалось открыть файл для записи.");

    // книги
    for (const auto& b : books) {
        fout << "BOOK\n";
        fout << "Title: " << b.getTitle() << "\n";
        fout << "Author: " << b.getAuthor() << "\n";
        fout << "Year: " << b.getYear() << "\n";
        fout << "ISBN: " << b.getISBN() << "\n";
        fout << "Available: " << (b.getAvailable() ? "yes" : "no") << "\n";
        fout << "BorrowedBy: " << b.getBorrowedBy() << "\n\n";
    }

    fout << "---USERS---\n";

    // пользователи
    for (const auto& u : users) {

        fout << "USER\n";
        fout << "Name: " << u.getName() << "\n";
        fout << "UserID: " << u.getUserId() << "\n";
        fout << "BorrowedBooks: ";
        const auto& list = u.getBorrowedBooks();

        for (size_t i = 0; i < list.size(); i++) {
            fout << list[i];
            if (i + 1 < list.size()) fout << "|";
        }

        fout << "\n";
        fout << "MaxBooks: " << u.getMaxBooksAllowed() << "\n\n";
    }

    fout.close();
}