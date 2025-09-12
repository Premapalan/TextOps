#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <regex>
#include <utility>
#include "fmt/args.h"

namespace textops
{
    template <typename... Args>
    class Msg
    {
        std::string key_;
        std::tuple<Args...> args_;
        template <typename... ArgsT>
        std::string format_helper(const std::string &key, const std::tuple<ArgsT...> &args) const
        {
            return std::apply([key](auto &&...unpackedArgs)
                              { return fmt::format(key, std::forward<decltype(unpackedArgs)>(unpackedArgs)...); }, args);
        }

    public:
        Msg(const std::string &key, Args &&...args)
            : key_(key), args_(std::forward<Args>(args)...) {}

        const std::string &getKey() const { return key_; }

        const std::tuple<Args...> &getArgs() const { return args_; }

        std::string getFormat() const { return format_helper(key_, args_); }

        std::vector<std::string> getTags() const
        {
            std::vector<std::string> tags;
            std::regex rgx("\\{([^{}]+)\\}");
            auto begin = std::sregex_iterator(key_.begin(), key_.end(), rgx);
            auto end = std::sregex_iterator();

            for (auto it = begin; it != end; ++it)
                tags.push_back((*it)[1].str());
            return tags;
        }
    };
}