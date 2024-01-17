#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <string>
#include <cctype>
#include <UnitTest++/TestReporterStdout.h>
#include "modAlphaCipher.h"
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////

auto RunSuite (const char* SuiteName)
{ 
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(),
                                SuiteName,
                                UnitTest::True(),0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

SUITE(KeyTest) {
    
    TEST(test1) {
        CHECK(modAlphaCipher(L"ПЕНЗА").encrypt(L"КЛЮЧИ") == L"ЪРЛЯИ");
    }
    
    TEST(test2) {
        CHECK(modAlphaCipher(L"ТЁМАТЁМА").encrypt(L"ЛЮБОВ") == L"ЮДНОФ");
    }
    
    TEST(test3) {
        CHECK(modAlphaCipher(L"пенза").encrypt(L"ключи") == L"ЪРЛЯИ");
    }
    
    TEST(test4) {
        CHECK_THROW(modAlphaCipher(L"ЧЕБУРЕК13"), cipher_error);
    }
    
    TEST(test5) {
        CHECK_THROW(modAlphaCipher(L"ДЖ!ЕК"), cipher_error);
    }
    
    TEST(test6) {
        CHECK_THROW(modAlphaCipher(L"КУ ЗЯ"), cipher_error);
    }
    
    TEST(test7) {
        CHECK_THROW(modAlphaCipher(L""), cipher_error);
    }
};

struct KeyB_fixture {
modAlphaCipher * p;
KeyB_fixture()
{ p = new modAlphaCipher(L"В");
}
~KeyB_fixture()
{ delete p;
}
};

/////////////////////////////////////////////////////////////////////////////////////////////////

SUITE(EncryptTest) {
    
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"));
        }
        
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"));
        }
        
    TEST_FIXTURE(KeyB_fixture, WhitSpace) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГДЕЁЖЗ ИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"));
        }
        
    TEST_FIXTURE(KeyB_fixture, Numbers) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГДЕЁЖЗИЙКЛМ3976НОПРСТУ286ФХЦЧШЩЪЫЬЭЮЯ"));
        }
        
    TEST_FIXTURE(KeyB_fixture, Empty) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
        }
        
    TEST_FIXTURE(KeyB_fixture, NoAlpha) {
        CHECK_THROW(p->encrypt(L"89869406908!"), cipher_error);
        }
        
    TEST(MaxShiftKey) {
        CHECK(L"ЯАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮ" == modAlphaCipher(L"Я").encrypt(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"));
        }
};

/////////////////////////////////////////////////////////////////////////////////////////////////

SUITE(DecryptTest) {
    
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" == p->decrypt(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ"));
        }
        
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"), cipher_error);
        }
        
    TEST_FIXTURE(KeyB_fixture, WhitSpace) {
        CHECK_THROW(p->decrypt(L"А Б В Г Д Е Ё Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я"), cipher_error);
        }
        
    TEST_FIXTURE(KeyB_fixture, Digit) {
        CHECK_THROW(p->decrypt(L"ДЕДМАКАР228"), cipher_error);
        }
        
    TEST_FIXTURE(KeyB_fixture, Punct) {
        CHECK_THROW(p->decrypt(L"ЭЧ+ПОЧ+МАК"), cipher_error);
        }
        
    TEST_FIXTURE(KeyB_fixture, Empty) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
        }
        
    TEST_FIXTURE(KeyB_fixture, NoAlpha) {
        CHECK_THROW(p->decrypt(L"%3146854326984"), cipher_error);
        }
        
    TEST(MaxShiftKey) {
        CHECK(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" == modAlphaCipher(L"Я").decrypt(L"ЯАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮ"));
        }
};

/////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    return UnitTest::RunAllTests();
}
