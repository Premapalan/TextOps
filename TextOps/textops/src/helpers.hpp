#pragma once
#include <string_view>
#include <iostream>

namespace textops
{
    namespace helper
    {
        void print(std::string_view message)
        {
            std::cout << message << std::endl;
        }
    }
}