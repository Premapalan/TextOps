#pragma once

#include "textHandler.hpp"

namespace textops
{
    template <typename... Args>
    Msg<Args...>::Msg(const std::string& key, Args&&... args)
        : key_(key), args_(std::forward<Args>(args)...)
    {
        assert(!key_.empty() && "Key should not be empty");
    }

    template <typename... Args>
    const std::string& Msg<Args...>::getKey() const { return key_; }

    template <typename... Args>
    const std::tuple<Args...>& Msg<Args...>::getArgs() const { return args_; }

    template <typename... Args>
    void Msg<Args...>::populateStoreWithTaggedArgs(const std::vector<std::string>& tags)
    {
        assert(tags.size() == sizeof...(Args) && "Tags count must match args count");
        store_.clear();
        std::size_t index = 0;
        std::apply([&](const auto &...unpackedArgs)
                   { ((store_.push_back(fmt::arg(tags[index++].c_str(), unpackedArgs))), ...); }, args_);
    }

    template <typename... Args>
    void Msg<Args...>::rebuildStore()
    {
        store_.clear();
        for (auto& [tag, val] : arg_map_)
        {
            std::visit([&](auto&& v)
                       { store_.push_back(fmt::arg(tag.c_str(), v)); }, val);
        }
    }

    template <typename... Args>
    template <typename T1>
    void Msg<Args...>::assignParameterValue(const std::string& tag, T1&& val)
    {
        assert(!tag.empty() && "Tag must not be empty");
        arg_map_[tag] = std::forward<T1>(val);
        rebuildStore();
    }

    template <typename... Args>
    std::vector<std::string> Msg<Args...>::extractFormatTags() const
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

    template <typename... Args>
    std::string Msg<Args...>::formatMessage()
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

    template <typename... Args>
    std::string Msg<Args...>::formatMessage(const fmt::dynamic_format_arg_store<fmt::format_context>& store)
    {
        return fmt::vformat(key_, store);
    }

    template <typename... Args>
    const fmt::dynamic_format_arg_store<fmt::format_context>& Msg<Args...>::getArgumentStore() const
    {
        return store_;
    }
} // namespace textops