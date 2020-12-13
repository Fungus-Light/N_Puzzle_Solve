#include "../INCLUDES/Util.h"

int Util::SefeInputInt(const char *tip, int min, int max)
{
    int temp = -100;
    std::cin >> temp;
    while (temp > max || temp < min || std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        std::cout << tip;
        std::cin >> temp;
    }
    return temp;
}

void Util::PrintLine(const char *message)
{
    std::cout << message << "\n";
}

void Util::PrintLine(int number)
{
    std::cout << number << "\n";
}

void Util::PrintLine(const std::string message)
{
    std::cout << message << "\n";
}

void Util::PrintArray(int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        std::cout << array[i];
    }
    std::cout << "\n";
}

std::string Util::Stringfy(int number)
{
    return std::to_string(number);
}