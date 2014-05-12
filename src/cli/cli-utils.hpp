#ifndef ANKI_LITE_CLI_UTILS_HPP
#define ANKI_LITE_CLI_UTILS_HPP

#include <functional>
#include <vector>
#include <string>

class CliCommand
{
public:
    CliCommand(const char *p_name1, std::function<bool (const std::string &)> func,
               const char * p_help_msg, const char *p_name2 = NULL,
               const char *p_name3 = NULL, const char *p_name4 = NULL);

    bool matches(const std::string &user_cmd) const;

    bool operator()(const std::string &s) const;

    std::string help_message() const;

private:

    std::vector<std::string> m_names;

    std::string m_help_message;

    std::function<bool (const std::string &)> m_func;
};

// helper functions
void tokenize_cmd(const std::string &cmd, std::vector<std::string> &tokens);

#endif
