#include "test.hpp"
#include <iostream>

void testFn()
{
    textops::Msg<std::string, int> msg("My name is {name} & {age}");
    fmt::dynamic_format_arg_store<fmt::format_context> store{};
    store.push_back(fmt::arg("name", "Pras"));
    store.push_back(fmt::arg("age", "10"));

    std::cout << msg.formatMessageWithStore(store) << std::endl;
}