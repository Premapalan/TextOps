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
        void populateStoreWithTaggedArgs(const std::vector<std::string> &tags)
        {
            store_.clear();

            std::size_t index = 0;
            std::apply([&](const auto &...unpackedArgs)
                       { ((store_.push_back(fmt::arg(tags[index++].c_str(), unpackedArgs))), ...); }, args_);
        }

    public:
        Msg(const std::string &key) : key_(key), args_() {}

        Msg(const std::string &key, Args &&...args)
            : key_(key), args_(std::forward<Args>(args)...) {}

        const std::string &getKey() const { return key_; }

        const std::tuple<Args...> &getArgs() const { return args_; }

        std::vector<std::string> extractFormatTags() const
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

        std::string formatMessage()
        {
            auto tags = extractFormatTags();
            populateStoreWithTaggedArgs(tags);
            return store_.size() > 0 ? fmt::vformat(key_, store_) : key_;
        }

        std::string formatMessageWithStore(const fmt::dynamic_format_arg_store<fmt::format_context> &store)
        {
            return fmt::vformat(key_, store_);
        }

        // Access the store member publicly if needed
        const fmt::dynamic_format_arg_store<fmt::format_context> &getArgumentStore() const { return store_; }
    };

} // namespace textops