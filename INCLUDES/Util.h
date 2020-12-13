#pragma once
//给编译器看，说明这个头文件只包含一次
#include <iostream>
#include <string>

class Util
{
public:
    ///打印一行信息，避免引入std；
    static void PrintLine(const char *message);
    static void PrintLine(int number);
    static void PrintLine(const std::string message);
    ///打印数组
    static void PrintArray(int *array, int length);
    ///安全的输入一个整数
    static int SefeInputInt(const char *tip, int min, int max);
    ///整数转字符串
    static std::string Stringfy(int number);
};