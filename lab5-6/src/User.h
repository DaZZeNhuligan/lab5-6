#ifndef USER_H
#define USER_H
#include <string>  // для имени и ID
#include <vector> // список взятых книг
// объявляем класс с скрытыми данными и открытыми 
class User{
    private:
    std::string name; // фамилия
    std::string userId; // ID вида USR_001
    std::vector<std::string> borrowedBooks; // список взятых  ИСБН
    int maxBooksAllowed; // лимит книг (по умолчанию 3)

    public:
    User(); // пустой конструктор для загрузки из файла
    //конструктор передачи пареметров 
    User(const std::string& n, const std::string& id );

    // геттеры инкапсуляции, доступ к приватным данным 
    std::string getName() const;
    std::string getUserId() const;
    const std::vector<std::string>& getBorrowedBooks() const; //возвращается по ссылки чтобы не копировать весь список 
    int getMaxBooksAllowed() const;

    // методы
    bool canBorrowMore() const;          // проверяет достиг ли пользователь лимита 
    void addBook(const std::string& isbn);  // добавляет ИСБН в список взятых книг
    void removeBook(const std::string& isbn); // удаляет  ИСБН из списка при возврате

    void displayProfile() const;         // выводит информацию о пользователе

    // методы для загрузки данных из файла
    void setBorrowedBooks(const std::vector<std::string>& list);
    void setMaxBooks(int m);
};



#endif