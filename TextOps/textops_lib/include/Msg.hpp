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
{ /**
   * @brief Generic message formatting utility.
   *
   * The Msg class encapsulates a message key and a variadic set of arguments, which can be mapped with tags for flexible formatting.
   * Uses the fmt library for runtime message composition.
   *
   * Example usage:
   * @code
   * textops::Msg<int, std::string> m("error_count", 5, "file.txt");
   * m.assignParameterValue("count", 5);
   * m.assignParameterValue("filename", "file.txt");
   * std::string result = m.formatMessage();
   * @endcode
   *
   * @tparam Args Variadic list of types for message arguments.
   *
   * @see fmt::dynamic_format_arg_store
   */
    template <typename... Args>
    class Msg
    {
        /**
         * The message key identifying the format template.
         */
        std::string key_;

        /**
         * Tuple storing the message parameters.
         */
        std::tuple<Args...> args_;

        /**
         * Store for dynamic arguments formatted with fmt.
         */
        fmt::dynamic_format_arg_store<fmt::format_context> store_;

        /**
         * @brief Variant type for storing heterogeneous argument values.
         */
        using ArgValue = std::variant<int, double, std::string, const char *, bool>;

        /**
         *  Map of tag names to argument values.
         */
        std::unordered_map<std::string, ArgValue> arg_map_;

        /**
         * @brief Fills the fmt argument store with values based on provided tags.
         * @param tags Vector of string tags corresponding to parameters.
         */
        void populateStoreWithTaggedArgs(const std::vector<std::string> &tags);

        /**
         * @brief Rebuilds the fmt argument store from the current argument map.
         */
        void rebuildStore();

    public:
        /**
         * @brief Constructs a Msg with key and parameters.
         * @param key The message format key identifier.
         * @param args Forwarded parameter pack of message arguments.
         */
        Msg(const std::string &key, Args &&...args);

        /**
         * @brief Gets the message key.
         * @return const reference to the key string.
         */
        const std::string &getKey() const;

        /**
         * @brief Returns the tuple of message arguments.
         * @return const reference to the arguments tuple.
         */
        const std::tuple<Args...> &getArgs() const;

        /**
         * @brief Assigns or updates a parameter value by its tag.
         * @tparam T1 Type of the value to assign (deduced).
         * @param tag The tag associated with the parameter.
         * @param val The value to assign to the tag.
         */
        template <typename T1>
        void assignParameterValue(const std::string &tag, T1 &&val);

        /**
         * @brief Extracts all format tags present in the message key.
         * @return A vector of strings with the tags found.
         */
        std::vector<std::string> extractFormatTags() const;

        /**
         * @brief Formats the message using the current argument store.
         * @return The formatted message string.
         */
        std::string formatMessage();

        /**
         * @brief Formats the message using a provided fmt argument store.
         * @param store The fmt::dynamic_format_arg_store to use for formatting.
         * @return The formatted message string.
         */
        std::string formatMessage(const fmt::dynamic_format_arg_store<fmt::format_context> &store);

        /**
         * @brief Returns the internal fmt argument store.
         * @return const reference to the argument store.
         */
        const fmt::dynamic_format_arg_store<fmt::format_context> &getArgumentStore() const;
    };

} // namespace textops

#include "Msg.tpp" // Implementation file for templates
