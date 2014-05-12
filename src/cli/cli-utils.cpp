#include "cli-utils.hpp"

using namespace std;

//-- CliCommand class implementation

CliCommand::CliCommand(const char *p_name1, std::function<bool (const string &)> func,
                       const char * p_help_msg, const char *p_name2,
                       const char *p_name3, const char *p_name4)
  : m_help_message(p_help_msg), m_func(func)
{
    m_names.push_back(p_name1);
    if (p_name2) {
        m_names.push_back(p_name2);
    }
    if (p_name3) {
        m_names.push_back(p_name3);
    }
    if (p_name4) {
        m_names.push_back(p_name4);
    }
}


bool CliCommand::matches(const string &cmd) const
{
    for (unsigned i = 0; i < m_names.size(); i++) {
        if (cmd == m_names[i]) {
            return true;
        }
    }
    return false;
}

bool CliCommand::operator()(const string &s) const
{
    return m_func(s);
}


std::string CliCommand::help_message() const
{
    return m_help_message;
}

//-- end CliCommand class implementation


/**
 * Split the command from the user in tokens (words).
 *
 * @todo Needs optimizations. :fixme:
 */
void tokenize_cmd(const string &cmd, vector<string> &tokens)
{
    if (cmd.empty()) {
        return;
    }
    size_t next_separator = cmd.find_first_of(" \t");
    if (next_separator == cmd.npos) {
        if (!cmd.empty()) {
            tokens.push_back(cmd);
        }
        return;
    }
    string new_token = cmd.substr(0, next_separator);
    if (!new_token.empty()) {
        tokens.push_back(new_token);
    }
    string rest_string = cmd.substr(next_separator + 1, cmd.npos);
    tokenize_cmd(rest_string, tokens);
}
