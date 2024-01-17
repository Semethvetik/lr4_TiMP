
/** @file
 * @author Сорокина С. В.
 * @version 1.0
 * @date 17.01.2024
 * @copyright ИБСТ ПГУ
 * @brief Заголовочный файл для модуля modAlphaCipher
 */

/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <locale>
#include <codecvt>
#include <algorithm>
using namespace std;

/**
* @brief Класс для шифрования и расшифрования текста с помощью алгоритма модифицированного алфавитного шифра
*
* @brief Класс имеет встроенный алфавит, состоящий из заглавных букв русского алфавита.
* @brief Ключ шифрования задается при создании объекта класса.
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class modAlphaCipher
{
    
private:
    int kolvostolbov;
    
public:
    modAlphaCipher() = delete;
    modAlphaCipher(const int& key) :kolvostolbov(key) {};    //конструктор
    
    /// Метод для зашифрования текста
    string encrypt(const string& open_stroka);               //зашифрование
    
    /// Метод для расшифрования текста
    string decrypt(const string& cipher_stroka);             //расшифрование
    string getValidText(const std::string & s);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class cipher_error: public std::invalid_argument
{
    
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
