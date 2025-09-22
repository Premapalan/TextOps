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

        // Push tags and corresponding args into the store
        void populateStoreWithTaggedArgs(const std::vector<std::string> &tags)
        {
            assert(tags.size() == sizeof...(Args) && "Tags count must match args count");

            store_.clear();
            std::size_t index = 0;
            std::apply([&](const auto &...unpackedArgs)
                       { ((store_.push_back(fmt::arg(tags[index++].c_str(), unpackedArgs))), ...); }, args_);
        }

        void rebuildStore()
        {
            store_.clear();
            for (auto &[tag, val] : arg_map_)
            {
                std::visit([&](auto &&v)
                           { store_.push_back(fmt::arg(tag.c_str(), v)); }, val);
            }
        }

    public:
        Msg(const std::string &key, Args &&...args)
            : key_(key), args_(std::forward<Args>(args)...)
        {
            assert(!key_.empty() && "Key should not be empty");
        }

        const std::string &getKey() const { return key_; }

        const std::tuple<Args...> &getArgs() const { return args_; }

        template <typename T1>
        void assignParameterValue(const std::string &tag, T1 &&val)
        {
            assert(!tag.empty() && "Tag must not be empty");
            arg_map_[tag] = std::forward<T1>(val);
            rebuildStore();
        }

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
            if (store_.size() == 0)
            {
                populateStoreWithTaggedArgs(extractFormatTags());
            }
            if (!arg_map_.empty())
            {
                rebuildStore();
            }
            return store_.size() > 0 ? fmt::vformat(key_, store_) : key_;
        }

        std::string formatMessage(const fmt::dynamic_format_arg_store<fmt::format_context> &store)
        {
            return fmt::vformat(key_, store);
        }

        // Access the store member publicly if needed
        const fmt::dynamic_format_arg_store<fmt::format_context> &getArgumentStore() const { return store_; }
    };

} // namespace textops