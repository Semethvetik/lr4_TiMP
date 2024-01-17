#include "modAlphaCipher.h"
#include <UnitTest++/UnitTest++.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Тесты ключей
SUITE (KeyTest) {
    
    string test = "BIGPINKPIG";
    int k;
    
    TEST (test1) {
        modAlphaCipher kluch(6);
        CHECK_EQUAL(kluch.encrypt(test),"NIPGGIIPBK");
    }
    
    TEST(test2) {
        modAlphaCipher kluch(-8);
        CHECK_THROW(kluch.encrypt(test), cipher_error);
    }
    
    TEST(test3) {
        modAlphaCipher kluch(69);
        CHECK_THROW(kluch.encrypt(test), cipher_error);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Тесты encrypt
SUITE(EncryptTest) {
    
    TEST(UpCaseString) {
        modAlphaCipher kluch(6);
        CHECK_EQUAL(kluch.encrypt("BIGPINKPIG"),"NIPGGIIPBK");
    }
    
    TEST(LowCaseString) {
        modAlphaCipher kluch(8);
        CHECK_EQUAL(kluch.encrypt("bigpinkpig"),"pknipgigbi");
    }
    
    TEST(LowUpCaseString) {
        modAlphaCipher kluch(9);
        CHECK_EQUAL(kluch.encrypt("bigPINKpig"),"ipKNIPgibg");
    }
    
    TEST(WithSpace) {
        modAlphaCipher kluch(6);
        CHECK_THROW(kluch.encrypt("BIG PINK PIG"), cipher_error);
    }
    
    TEST(Empty) {
        modAlphaCipher kluch(8);
        CHECK_THROW(kluch.encrypt(" "),cipher_error);
    }
    
    TEST(NoAlpha) {
        modAlphaCipher kluch(9);
        CHECK_THROW(kluch.encrypt("@#$12345"),cipher_error);
    }
    
    TEST(Numbers) {
        modAlphaCipher kluch(6);
        CHECK_THROW(kluch.encrypt("BIG123PINK456PIG"),cipher_error);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Тесты decrypt
SUITE(DecryptText) {
    
    TEST(UpCaseString) {
        modAlphaCipher kluch(6);
        CHECK_EQUAL(kluch.decrypt("NIPGGIIPBK"),"BIGPINKPIG");
    }
    
    TEST(LowUpCaseString) {
        modAlphaCipher kluch(9);
        CHECK_EQUAL(kluch.decrypt("ipKNIPgibg"),"bigPINKpig");
    }
    
    TEST(WithSpace) {
        modAlphaCipher kluch(6);
        CHECK_THROW(kluch.decrypt("BIG PINK PIG"),cipher_error);
    }
    
    TEST(Empty) {
        modAlphaCipher kluch(8);
        CHECK_THROW(kluch.decrypt(" "),cipher_error);
    }
    
    TEST(Digit) {
        modAlphaCipher kluch(9);
        CHECK_THROW(kluch.decrypt("BIG123PINK456PIG"),cipher_error);
    }
    
    TEST(WithSymbol) {
        modAlphaCipher kluch(6);
        CHECK_THROW(kluch.decrypt("BIG#$%PINKPIG"),cipher_error);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    return UnitTest::RunAllTests();
}
