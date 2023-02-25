#include "../string/string.hpp"
#include <iostream>
#include <string>
#include <cassert>

void testString() {

    // 測試構造函數
    String s1; // 默認構造函數創建一個空字符串
    assert(s1.empty()); // 斷言字符串是否為空

    String s2("hello"); // 使用一個字符串字面值初始化字符串對象
    assert(s2.size() == 5); // 斷言字符串長度是否為5

    String s3(s2); // 使用一個現有的字符串對象初始化新的字符串對象
    assert(s3 == s2); // 斷言兩個字符串對象是否相等

    // 測試賦值操作符
    s1 = s2; // 將一個字符串對象賦值給另一個字符串對象
    assert(s1 == s2); // 斷言兩個字符串對象是否相等

    s1 = "world"; // 將一個字符串字面值賦值給字符串對象
    assert(s1 == "world"); // 斷言字符串對象是否等於指定的字符串字面值

    // 測試拼接操作
    s1 += s2; // 將一個字符串對象附加到另一個字符串對象的末尾
    assert(s1 == "worldhello"); // 斷言兩個字符串是否相等

    s1 += "!"; // 將一個字符串字面值附加到字符串對象的末尾
    assert(s1 == "worldhello!"); // 斷言兩個字符串是否相等

    // 測試查找操作
    // assert(s1.find("hello") == 5); // 斷言查找子串的結果是否正確
    // assert(s1.find("world") == 0); // 斷言查找子串的結果是否正確
    // assert(s1.find("!") == 10); // 斷言查找子串的結果是否正確
    // assert(s1.find("foo") == string::npos); // 斷言查找子串的結果是否正確

    // 測試子字串操作
    assert(s1.substr(5, 5) == "hello"); // 斷言提取子串的結果是否正確

    // 測試比較操作
    assert(s1.compare("worldhello!") == 0); // 斷言兩個字符串是否相等
    assert(s1.compare("worldhello") > 0); // 斷言比較結果是否正確
    assert(s1.compare("x") < 0); // 斷言比較結果是否正確

    std::cout << "所有測試均已通過！" << '\n'; // 在結束測試後輸出一條信息
}
