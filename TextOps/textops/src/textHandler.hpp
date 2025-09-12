#pragma once

#include <fmt/args.h>
#include <string>
#include <tuple>
#include <vector>
#include <regex>

namespace textops
{
    template <typename... Args>
    class Msg
    {
        std::string key_;
        std::tuple<Args...> args_;
        fmt::dynamic_format_arg_store<fmt::format_context> store_;

        // Push tags and corresponding args into the store
        void push_args_with_tags(const std::vector<std::string> &tags)
        {
            store_.clear();

            std::size_t index = 0;
            std::apply([&](const auto &...unpackedArgs)
                       { ((store_.push_back(fmt::arg(tags[index++].c_str(), unpackedArgs))), ...); }, args_);
        }

    public:
        Msg(const std::string &key, Args &&...args)
            : key_(key), args_(std::forward<Args>(args)...) {}

        const std::string &getKey() const { return key_; }

        const std::tuple<Args...> &getArgs() const { return args_; }

        std::vector<std::string> getTags() const
        {
            std::vector<std::string> tags;
            std::regex rgx("\\{([^{}]+)\\}");
            auto begin = std::sregex_iterator(key_.begin(), key_.end(), rgx);
            auto end = std::sregex_iterator();
            for (auto it = begin; it != end; ++it)
            {
                tags.push_back((*it)[1].str());
            }
            return tags;
        }

        std::string getFormat()
        {
            auto tags = getTags();
            push_args_with_tags(tags);
            return fmt::vformat(key_, store_);
        }

        // Access the store member publicly if needed
        const fmt::dynamic_format_arg_store<fmt::format_context> &getStore() const { return store_; }
    };

} // namespace textops