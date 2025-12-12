#include "Book.h"
#include <iostream> // для вывода инфы
#include <stdexcept> // для исключений
#include <ctime> // для текущего года

// пустой конструктор где год 0, значит книга доступна
Book::Book()
    : year(0), isAvailable(true)
{
}

// конструктор с параметрами, присваиваем полученные значения
Book::Book(const std::string& t, const std::string& a, int y, const std::string& i) : title(t), author(a), year(y), isbn(i), isAvailable(true)
{
    // проверка корректности года
    time_t now = time(nullptr);
    int currentYear = localtime(&now)->tm_year + 1900; // tm хранит количество лет с 1900 года

    // проверка года издания (от 1450 до текущего)
    if (y < 1450 || y > currentYear) {
        throw std::invalid_argument("Некорректный год издания");
    }

    // проверка ИСБН
    if (i.empty()) {
        throw std::invalid_argument("ISBN не может быть пустым");
    }
}

// возвращаем значение привата  
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
std::string Book::getISBN() const { return isbn; }
bool Book::getAvailable() const { return isAvailable; }
std::string Book::getBorrowedBy() const { return borrowedBy; }

// метод - выдать книгу
void Book::borrowBook(const std::string& userName) {
    // проверка
    if (!isAvailable) {
        throw std::runtime_error("Книга уже выдана");
    }
    isAvailable = false;
    borrowedBy = userName;
}

// метод - вернуть книгу
void Book::returnBook() {
    // проверка
    if (isAvailable) {
        throw std::runtime_error("Книга уже находится в библиотеке");
    }
    isAvailable = true;
    borrowedBy = "";
}

// вывод информации
void Book::displayInfo() const {
    std::cout << "BOOK\n";
    std::cout << "Title: " << title << "\n";
    std::cout << "Author: " << author << "\n";
    std::cout << "Year: " << year << "\n";
    std::cout << "ISBN: " << isbn << "\n";
    std::cout << "Available: " << (isAvailable ? "yes" : "no") << "\n";
    std::cout << "BorrowedBy: " << borrowedBy << "\n\n";
}

// методы при загрузке данных из файла
void Book::setAvailable(bool a) {
    isAvailable = a;
}

void Book::setBorrowedBy(const std::string& name) {
    borrowedBy = name;
}