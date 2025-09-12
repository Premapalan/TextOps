#include "test.hpp"
#include <iostream>

void testFn()
{
    textops::Msg<std::string> msg("My name is {name}", "Prasath");
    std::cout << msg.getFormat() << std::endl;
}