#include "test.hpp"
#include <iostream>
#include <typeinfo>

// Test fixture for Msg template class
TEST(TextOpsMsgTest, ConstructionAndKeyAccess)
{
    textops::Msg<int, std::string> msg("Value: {val}, Name: {name}", 123, "Test");
    EXPECT_EQ(msg.getKey(), "Value: {val}, Name: {name}");
}

TEST(TextOpsMsgTest, ExtractFormatTags)
{
    textops::Msg<int, std::string> msg("Id: {id}, Label: {label}", 42, "demo");
    auto tags = msg.extractFormatTags();
    ASSERT_EQ(tags.size(), 2);
    EXPECT_EQ(tags[0], "id");
    EXPECT_EQ(tags[1], "label");
}

TEST(TextOpsMsgTest, FormatMessageWithArgs)
{
    textops::Msg<int, std::string> msg("A={a}, B={b}", 10, "xyz");
    std::string out = msg.formatMessage();
    EXPECT_EQ(out, "A=10, B=xyz");
}

TEST(TextOpsMsgTest, AssignParameterValue)
{
    textops::Msg<> msg("A={a}, B={b}");
    msg.assignParameterValue("a", 999);
    msg.assignParameterValue("b", "xyz");
    std::string out = msg.formatMessage();
    EXPECT_EQ(out, "A=999, B=xyz");
}
