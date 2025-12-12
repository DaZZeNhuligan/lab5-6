
#include "Library.h"
#include <iostream>
#include <string>

int main() {
    #ifdef _WIN32
    system("chcp 65001 > nul");   // включаем UTF-8 для Windows консоли
#endif
    
    // при запуске загружаем 
    Library lib("data/library_data.txt");

    int choice;

    while (true) {
        // меню 
        std::cout << "\n=== БИБЛИОТЕКА ===\n";
        std::cout << "1. Просмотреть все книги\n";
        std::cout << "2. Просмотреть всех пользователей\n";
        std::cout << "3. Добавить новую книгу\n";
        std::cout << "4. Зарегистрировать пользователя\n";
        std::cout << "5. Выдать книгу пользователю\n";
        std::cout << "6. Принять книгу от пользователя\n";
        std::cout << "7. Поиск книги по ISBN\n";
        std::cout << "8. Просмотреть профиль пользователя\n";
        std::cout << "9. Сохранить данные в файл\n";
        std::cout << "10. Выход\n";
        std::cout << "Ваш выбор: ";

        std::cin >> choice;

        // защита от некорректного ввода
        if (std::cin.fail()) {
            std::cin.clear(); // чистит ошибку
            std::cin.ignore(10000, '\n'); // убирает из буфера
            std::cout << "Ошибка ввода. Попробуйте ещё раз.\n";
            continue;
        }

        try {
            // показать все книги
            if (choice == 1) {
                lib.displayAllBooks();
            }
            // показать всех пользователей
            else if (choice == 2) {
                lib.displayAllUsers();
            }
            // добавить книгу
            else if (choice == 3) {
                std::string title, author, isbn;
                int year;

                std::cout << "Введите название: ";
                std::cin.ignore();
                std::getline(std::cin, title);

                std::cout << "Введите автора: ";
                std::getline(std::cin, author);

                std::cout << "Введите год: ";
                std::cin >> year;

                std::cout << "Введите ISBN: ";
                std::cin.ignore();
                std::getline(std::cin, isbn);
                // создаем объект книги
                Book book(title, author, year, isbn);
                // добавляем книгу в библиотеку
                lib.addBook(book);

                std::cout << "Книга успешно добавлена\n";
            }
            // регистрация пользователя
            else if (choice == 4) {
                std::string name, id;

                std::cout << "Введите фамилию пользователя: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                std::cout << "Введите ID (например USR_001): ";
                std::getline(std::cin, id);

                User u(name, id);

                lib.addUser(u);

                std::cout << "Пользователь зарегистрирован.\n";
            }
            // выдача книги
            else if (choice == 5) {
                std::string name, isbn;

                std::cout << "Введите фамилию пользователя: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                std::cout << "Введите ISBN книги: ";
                std::getline(std::cin, isbn);

                lib.borrowBook(name, isbn);

                std::cout << "Книга успешно выдана\n";
            }
            // возврат книги
            else if (choice == 6) {
                std::string isbn;

                std::cout << "Введите ISBN возвращаемой книги: ";
                std::cin.ignore();
                std::getline(std::cin, isbn);

                lib.returnBook(isbn);

                std::cout << "Книга успешно возвращена\n";
            }
            // поиск книги по ИСБН
            else if (choice == 7) {
                std::string isbn;

                std::cout << "Введите ISBN: ";
                std::cin.ignore();
                std::getline(std::cin, isbn);

                Book* b = lib.findBookByISBN(isbn);

                if (b)
                    b->displayInfo();
                else
                    std::cout << "Книга не найдена.\n";
            }
            // профиль пользователя 
            else if (choice == 8) {
                std::string name;

                std::cout << "Введите фамилию пользователя: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                User* u = lib.findUserByName(name);

                if (u)
                    u->displayProfile();
                else
                    std::cout << "Пользователь не найден.\n";
            }
            // сохраняет сессию
            else if (choice == 9) {
                lib.saveToFile();
                std::cout << "Данные успешно сохранены\n";
            }
            // выход
            else if (choice == 10) {
                std::cout << "Выход из программы\n";
                break;
            }
            else {
                std::cout << "Неверный пункт меню.\n";
            }
        }
        //все исключения из методов
        catch (const std::exception& ex) {
            std::cout << "Ошибка: " << ex.what() << "\n";
        }
    }

    return 0;
}