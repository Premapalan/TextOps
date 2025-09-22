#pragma once

#include <fmt/args.h>
#include <string>
#include <tuple>
#include <vector>
#include <regex>
#include <variant>
#include <unordered_map>
#include <cassert>

namespace textops
{
    template <typename... Args>
    class Msg
    {
        std::string key_;
        std::tuple<Args...> args_;
        fmt::dynamic_format_arg_store<fmt::format_context> store_;

        using ArgValue = std::variant<int, double, std::string, const char *, bool>;
        std::unordered_map<std::string, ArgValue> arg_map_;

        void populateStoreWithTaggedArgs(const std::vector<std::string> &tags);
        void rebuildStore();

    public:
        Msg(const std::string &key, Args &&...args);

        const std::string &getKey() const;
        const std::tuple<Args...> &getArgs() const;

        template <typename T1>
        void assignParameterValue(const std::string &tag, T1 &&val);

        std::vector<std::string> extractFormatTags() const;
        std::string formatMessage();
        std::string formatMessage(const fmt::dynamic_format_arg_store<fmt::format_context> &store);

        const fmt::dynamic_format_arg_store<fmt::format_context> &getArgumentStore() const;
    };

} // namespace textops

#include "textHandler.tpp" // Implementation file for templates
