#include "alphabet_identifiers_DLL.h"
#include <iostream>

int main(int args, char** argv)
{
    using namespace DynamicMathPower;
    {
        std::string identifier{ "A1-Z9" };
        alphabet_identifiers A;
        identifier = A.GenerateNextIdentifier(identifier);
        std::cout << identifier << std::endl;
        return 0;
    }
}