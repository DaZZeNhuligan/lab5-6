cmake_minimum_required(VERSION 3.10)

project(LibraryManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем папку с заголовочными файлами
include_directories(src)

# Создаем исполняемый файл из всех cpp файлов
add_executable(library
    src/main.cpp
    src/Book.cpp
    src/User.cpp
    src/Library.cpp
)