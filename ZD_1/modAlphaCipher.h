/** @file
 * @author Сорокина С. В.
 * @version 1.0
 * @date 17.01.2024
 * @copyright ИБСТ ПГУ
 * @brief Заголовочный файл для модуля modAlphaCipher
 */

/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include <string>
#include <map>
#include <codecvt>
#include <locale>
using namespace std;

/**  @brief  Класс для шифрования методом "Гронсвельда"
* @warning Работа с сообщениями на русском языке
* */

/////////////////////////////////////////////////////////////////////////////////////////////////

class modAlphaCipher
{
private:
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	
	/// @brief  Использует алфавит по порядку для шифрования методом "Гронсвельда"
	wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";  //алфавит по порядку
	
	/// @brief  Ассоциативный массив "номер по символу"
	map <wchar_t,int> alphaNum;                               //ассоциативный массив "номер по символу"
	
	/// @brief  Атрибут для хранения ключа для шифрования и расшифрования
	vector <int> key;                                         //ключ
	
	/// @brief  Преобразование строка-вектор
	vector<int> convert(const wstring& ws);                   //преобразование строка-вектор
	
	/// @brief  Преобразование вектор-строка
	wstring convert(const vector<int>& v);                    //преобразование вектор-строка
	
	/// @brief  Валидация ключа
	wstring getValidKey(const wstring & ws);
	
	/// @brief Валидация текста при шифровании или расшифровании
	wstring getValidOpenText(const wstring & ws);
	wstring getValidCipherText(const wstring & ws);
    
public:

    /// @brief Запрет конструктора без параметров
	modAlphaCipher() = delete;                                //запретим конструктор без параметров
	
	/// @brief  Конструктор для установки ключа
	modAlphaCipher(const wstring& wskey);                     //конструктор для установки ключа
	
	/// @brief Метод для зашифрования
	wstring encrypt(const wstring& open_text);                //зашифрование
	
	/// @brief Метод для расшифрования
	wstring decrypt(const wstring& cipher_text);              //расшифрование
};

/////////////////////////////////////////////////////////////////////////////////////////////////

class cipher_error: public invalid_argument
{
public:
	explicit cipher_error (const string& what_arg):
		invalid_argument(what_arg) {}
	explicit cipher_error (const char* what_arg):
		invalid_argument(what_arg) {}
};
