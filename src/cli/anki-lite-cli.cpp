#include <iostream>
#include <string>
#include <functional>

#include "simple-db.hpp"

using namespace std;

class CliCommand
{
public:
    CliCommand(const char *p_name1, std::function<bool (const string &)> func,
               const char * p_help_msg, const char *p_name2 = NULL,
               const char *p_name3 = NULL, const char *p_name4 = NULL);

    bool matches(const std::string &user_cmd) const;

    bool operator()(const string &s) const;

    std::string help_message() const;

private:

    std::vector<std::string> m_names;

    std::string m_help_message;

    std::function<bool (const string &)> m_func;
};

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

//-- end CliCommand class implementation


bool print_help(const string &s="");

bool print_help(const string &)
{
    cout << "HELP" <<endl;
    return true;
}


bool process_cmd(const string &cmd, const vector<CliCommand> &available_cmds)
{
    bool rc = true;
    for (auto it = available_cmds.begin(); it != available_cmds.end(); it++) {
        if ((*it).matches(cmd)) {
            rc = (*it)(cmd);
            break;
        }
    };
    return rc;
}


/**
 * Populate 'commands' vector with available commands.
 */
void add_cmds(vector<CliCommand> &commands)
{
    commands.push_back(CliCommand("exit", [](const string&) -> bool { return false; },
                                  "Exit program", "quit", "q", "e"));
    commands.push_back(CliCommand("help", print_help,
                                  "Display help message", "h"));
}


int main(int, char **)
{
    string cmd;
    vector<CliCommand> commands;
    add_cmds(commands);
    while(1) {
        cin >> cmd;
        if (!process_cmd(cmd, commands)) {
            break;
        }
    }
}
