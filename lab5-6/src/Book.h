#ifndef BOOK_H
#define BOOK_H
#include <string>
// объявляем класс с скрытыми данными и открытыми 
class Book{
    private:
    std::string title; // название книги
    std::string author; // автор
    int year; // год издания
    std::string isbn; // ИСБН книжки
    bool isAvailable; // доступна ли книга(да,нет)
    std::string borrowedBy; //фамилия пользователя который взял книгу 

    public:
    Book(); //для загрузки из файла 

    //конструктор проверки года и ИСБН 
    Book(const std::string& t, const std::string& a, int y, const std::string& i );

    // геттеры инкапсуляции 
    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getISBN() const;
    bool getAvailable() const;
    std::string getBorrowedBy() const;

    // основные методы 
    void borrowBook(const std::string& userName); // выдать книгу
    void returnBook();                            // вернуть книгу
    void displayInfo() const;                     // показать информацию о книге

    // методы при загрузки данных из файла
    void setAvailable(bool a);
    void setBorrowedBy(const std::string& name);
};




#endif