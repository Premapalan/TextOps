#pragma once

#include <iostream>
#include <string_view>

namespace textops
{
    namespace helper
    {
        inline void print(std::string_view message)
        {
            std::cout << message << std::endl;
        }
    } // namespace helper
} // namespace textops