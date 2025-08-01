#pragma once

#include <iostream>
#include <string_view>
#include "fmt/args.h"

using DynamicArgStore = fmt::dynamic_format_arg_store<fmt::format_context>;
namespace textops
{
    namespace helper
    {
        constexpr const char *errorMsg = "The error {error} caused due to the invalid input number : {number}";
        inline void print(std::string_view message)
        {
            std::cout << message << std::endl;
        }

        inline void printFormat(std::string_view message)
        {
            auto formatted = fmt::format("formatted messsage is : {}", message);
            std::cout << formatted << std::endl;
        }

        inline void checkFormatArgs()
        {
            auto v = fmt::arg("a", 10);
            fmt::print("argument name : {} & arg value : {a}", v.name, fmt::arg("a", 10));
        }

        inline void testSimpleTextwithParams()
        {
            fmt::dynamic_format_arg_store<fmt::format_context> store;
            store.push_back(fmt::arg("error", "Invalid-Input-Number"));
            store.push_back(fmt::arg("number", 25));

            testPassingStore(errorMsg, store);
        }

        inline void testPassingStore(std::string_view message, const DynamicArgStore &store)
        {
            std::string s = fmt::vformat(message, store);
            fmt::print("{}\n", s);
        }
    } // namespace helper
} // namespace textops