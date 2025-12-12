#include "User.h"
#include <iostream>  // вывод инфы
#include <algorithm>  // нужен для поиска ИСБН в векторе
#include <stdexcept>  // исключения

// пустой конструктор
User::User()
    : maxBooksAllowed(3)     // пользователь может взять 3 книги по умолчанию
{
}

// конструктор с именем и ID пользователя
User::User(const std::string& n, const std::string& id) : name(n), userId(id), maxBooksAllowed(3) // заполняем имя, ID, лимит
{
    //проверка
    if (name.empty() || userId.empty()) {
        throw std::invalid_argument("Имя и ID пользователя не могут быть пустыми.");
    }
}

// геттеры, возвращение знаения из привата
std::string User::getName() const { return name;}
std::string User::getUserId() const {return userId;}
const std::vector<std::string>& User::getBorrowedBooks() const {return borrowedBooks;}
int User::getMaxBooksAllowed() const {return maxBooksAllowed;}

// проверка, можно ли пользователю взять книгу
bool User::canBorrowMore() const {
    //количество уже взятых < лимит 
    return borrowedBooks.size() < (size_t)maxBooksAllowed;
}

// добавление книги пользователю
void User::addBook(const std::string& isbn) {
    //проверка
    if (!canBorrowMore()) {
        throw std::runtime_error("Пользователь уже достиг лимита книг.");
    }
    //добавление в конец списка
    borrowedBooks.push_back(isbn);
}

// удаление книги по ИСБН
void User::removeBook(const std::string& isbn) {
    // ищем ИСБН 
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
    // если не найден
    if (it == borrowedBooks.end()) {
        throw std::runtime_error("Пользователь не брал книгу с таким ISBN.");
    }
    // если нашли удалим 
    borrowedBooks.erase(it);
}

// вывод информации пользователя
void User::displayProfile() const {
    std::cout << "USER\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "UserID: " << userId << "\n";
     //выводим список книг
    std::cout << "BorrowedBooks: ";
    // проверка пусйтой ли список 

    if (borrowedBooks.empty()) {
        std::cout << "\n";
    } else {
        // выводим каждый если не пустой
        for (size_t i = 0; i < borrowedBooks.size(); i++) {
            std::cout << borrowedBooks[i];
            // без первого и последнего разделителя
            if (i + 1 < borrowedBooks.size()) {
                std::cout << "|";  
            }
        }
        std::cout << "\n";
    }
    // максимум книг
    std::cout << "MaxBooks: " << maxBooksAllowed << "\n\n";
}

// для загрузки данных из файла 
void User::setBorrowedBooks(const std::vector<std::string>& list) {
    borrowedBooks = list;
}

void User::setMaxBooks(int m) {
    maxBooksAllowed = m;
}