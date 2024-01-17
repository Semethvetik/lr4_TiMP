/** @file
 * @author Сорокина С. В.
 * @version 1.0
 * @date 17.01.2024
 * @copyright ИБСТ ПГУ
 * @brief Заголовочный файл для модуля modAlphaCipher
 */

/////////////////////////////////////////////////////////////////////////////////////////////////

#include "modAlphaCipher.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///@brief Метод для расшифрования
string modAlphaCipher::decrypt(const std::string& cipher_stroka)              //расшифрование
{
    string s = getValidText(cipher_stroka);
    string ocs = s;
    int dlina, kolvostrok, pozitsiya, a; 
    dlina = s.size();
    kolvostrok = (dlina - 1) / kolvostolbov + 1;
    a = 0;
    for (int nomerstolba = kolvostolbov; nomerstolba > 0; nomerstolba--) { 
        for (int line_number = 0; line_number < kolvostrok; line_number++) { 
            pozitsiya = kolvostolbov * line_number + nomerstolba;
            if (pozitsiya - 1 < dlina) {
                ocs[pozitsiya - 1] = s[a];
                a++;
            }
        }
    }
    return ocs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///@brief Метод для зашифрования
string modAlphaCipher::encrypt(const string& open_stroka)                     //зашифрование
{
    string s = getValidText(open_stroka);
    string ocs = s;
    int dlina, kolvostrok, pozitsiya, a; 
    dlina = s.size();
    kolvostrok = (dlina - 1) / kolvostolbov + 1; 
    a = 0;
    for (int nomerstolba = kolvostolbov; nomerstolba > 0; nomerstolba--) { 
        for (int line_number = 0; line_number < kolvostrok; line_number++) {
            pozitsiya = nomerstolba + kolvostolbov * line_number;
            if (pozitsiya-1 < dlina) {
                ocs[a] = open_stroka[pozitsiya-1];
                a++;
            }
        }
    }
    return ocs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///@brief Метод для проверки текста на валидность
inline std::string modAlphaCipher::getValidText(const std::string & s)
{
	if (s.empty()) {
        throw cipher_error("Input text cannot be empty");
    }
    
    if (static_cast<std::string::size_type>(kolvostolbov) > s.length()) {
        throw cipher_error("Invalid key");
    }
    
    for (char c : s) {
        if (!isalpha(c)) {
            throw cipher_error("Invalid characters");
        }
    }
    
    return s;
}
