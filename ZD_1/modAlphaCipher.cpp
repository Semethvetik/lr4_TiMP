/** @file
 * @author Сорокина С. В.
 * @version 1.0
 * @date 17.01.2024
 * @copyright ИБСТ ПГУ
 * @brief Заголовочный файл для модуля modAlphaCipher
 */

/////////////////////////////////////////////////////////////////////////////////////////////////

#include "modAlphaCipher.h"
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////

modAlphaCipher::modAlphaCipher(const wstring& wskey)
{
    for (unsigned i=0; i<numAlpha.size(); i++) {
        alphaNum[numAlpha[i]]=i;
    }
    key = convert(getValidKey(wskey));
}

/////////////////////////////////////////////////////////////////////////////////////////////////

///@brief Метод для зашифрования
wstring modAlphaCipher::encrypt(const wstring& open_text)
{
    vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

///@brief Метод для расшифрования
wstring modAlphaCipher::decrypt(const wstring& cipher_text)
{
    vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

inline vector<int> modAlphaCipher::convert(const wstring& ws)
{
    vector<int> result;
    for(auto c:ws) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

inline wstring modAlphaCipher::convert(const vector<int>& v)
{
    wstring result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

///@brief Метод для проверки ключа на валидность
inline wstring modAlphaCipher::getValidKey(const wstring & ws)
{
    if (ws.empty())
        throw cipher_error("Empty key!");
    wstring tmp(ws);
    string s = codec.to_bytes(ws);
    for (auto & c:tmp) {
        if (!iswalpha(c)) {
            throw cipher_error(string("Invalid key ") + "'" + s + "'" + "!");
        }
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

///@brief Метод для проверки принятого текста на валидность
inline wstring modAlphaCipher::getValidOpenText(const wstring & ws)
{

    wstring tmp;
    for (auto c:ws) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty text!");
    return tmp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

///@brief Метод для проверки зашифрованного текста на валидность
inline wstring modAlphaCipher::getValidCipherText(const wstring & ws)
{
    if (ws.empty())
        throw cipher_error("Empty text!");
    for (auto c:ws) {
        string s = codec.to_bytes(ws);
        if (!iswupper(c))
            throw cipher_error(string("Invalid text ") + "'" + s + "'" + "!");
    }
    return ws;
}
