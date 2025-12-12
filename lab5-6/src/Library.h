#ifndef LIBRARY_H
#define LIBRARY_H
#include <string>  // строки
#include <vector> // список книг и пользователей
#include "Book.h" // работаем с книгами
#include "User.h" // работаем с пользователями

class Library{
    private:
    std::vector<Book> books; // каталог книг
    std::vector<User> users; // список пользователей
    std::string dataFile; // путь к файлу

    public:
    // конструктор принимает путь к файлу и подгружает его
    Library(const std::string& file);

    // добавления в вектора
    void addBook(const Book& book);
    void addUser(const User& user);

    // поиск(вернут либо адрес, либо nullptr)
    Book* findBookByISBN(const std::string& isbn);
    User* findUserByName(const std::string& name);

    //для выдачи и возврата книг
    void borrowBook(const std::string& userName, const std::string& isbn);
    void returnBook(const std::string& isbn);

    //вывод списка
    void displayAllBooks() const;
    void displayAllUsers() const;

    // работа с файлом
    void saveToFile() const;
    void loadFromFile();
};
#endif