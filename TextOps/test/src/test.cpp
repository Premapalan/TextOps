#include "test.hpp"
#include <iostream>
#include <typeinfo>

void testFn()
{
    textops::Msg<> msg1("My name is {name} & {age}");
    msg1.assignParameterValue("name", "Prasa");
    msg1.assignParameterValue("age", 10);

    std::cout << msg1.formatMessage() << std::endl;

    textops::Msg<> msg2("My name is Prasath Premapalan");
    std::cout << msg2.formatMessage() << std::endl;

    textops::Msg<std::string, std::string> msg3("My name is {name} and last name is {lastName}", "Prasath", "Premapalan");
    std::cout << msg3.formatMessage() << std::endl;

    int x = 42;
    std::cout << "Type of x: " << typeid(x).name() << std::endl;

    std::cout << "Type of x: " << typeid("Prasath").name() << std::endl;
}