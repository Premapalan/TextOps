#include "test.hpp"
#include <iostream>

void testFn()
{
    textops::Msg<std::string, int> msg1("My name is {name} & {age}");
    fmt::dynamic_format_arg_store<fmt::format_context> store{};
    store.push_back(fmt::arg("name", "Pras"));
    store.push_back(fmt::arg("age", "10"));

    std::cout << msg1.formatMessageWithStore(store) << std::endl;

    textops::Msg<> msg2("My name is Prasath Premapalan");
    std::cout << msg2.formatMessage() << std::endl;
}