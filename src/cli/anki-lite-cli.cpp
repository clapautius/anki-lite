#include <iostream>
#include <string>
#include <functional>

#include "simple-db.hpp"
#include "cli-utils.hpp"
#include "collection.hpp"
#include "simple-db.hpp"
#include "exceptions.hpp"

using namespace std;
using namespace anki_lite;

vector<CliCommand> g_cli_commands;
anki_lite::Collection g_collection;


bool print_help(const string &s="");

bool print_help(const string &)
{
    cout << "Available commands:" << endl;
    for (unsigned i = 0; i < g_cli_commands.size(); i++) {
        cout << " - " << g_cli_commands[i].help_message() << endl;
    }
    return true;
}


/**
 * Load a collection from a simple-db file.
 * Uses the 'g_collection' global var.
 */
bool load_collection(const string &cmd)
{
    vector<string> tokens;
    tokenize_cmd(cmd, tokens);
    if (tokens.size() < 2) {
        cout << "Invalid command" << endl;
    } else {
        anki_lite::SimpleDb db(tokens[1]);
        db.open_storage();
        db.get_collection(g_collection);
    }
    return true;
}


/**
 * Save a collection to a simple-db file.
 * Uses the 'g_collection' global var.
 */
bool save_collection(const string &cmd)
{
    vector<string> tokens;
    tokenize_cmd(cmd, tokens);
    if (tokens.size() < 2) {
        cout << "Invalid command" << endl;
    } else {
        anki_lite::SimpleDb db(tokens[1]);
        db.open_storage();
        db.write_collection(g_collection);
    }
    return true;
}


bool add_deck_to_collection(const string &cmd)
{
    vector<string> tokens;
    tokenize_cmd(cmd, tokens);
    if (tokens.size() < 2) {
        cout << "Invalid command" << endl;
    } else {
        TextMapT details;
        details["name"] = tokens[1];
        Deck deck(0, details);
        g_collection.add_deck(deck);
    }
    return true;
}


bool process_cmd(const string &full_cmd, const vector<CliCommand> &commands)
{
    bool rc = true;
    bool found = false;
    for (auto it = commands.begin(); it != commands.end() && !found; it++) {
        // extract first word
        string cmd = full_cmd.substr(0, full_cmd.find_first_of(" \t"));
        if ((*it).matches(cmd)) {
            try {
                rc = (*it)(full_cmd);
                cout << "> ";
            }
            catch (std::runtime_error &e) {
                cout << "Error executing command: " << e.what() << endl;
            }
            catch (...) {
                cout << "Unknown error executing command." << endl;
            }
            found = true;
        }
    };
    if (!found) {
        cout << "Unknown command" << endl;
    }
    return rc;
}


/**
 * Populate 'commands' vector with available commands.
 */
void init_cmds(vector<CliCommand> &commands)
{
    commands.push_back(CliCommand("exit", [](const string&) -> bool { return false; },
                                  "exit | quit | e | q : exit program", "quit", "q","e"));
    commands.push_back(CliCommand("help", print_help,
                                  "help | h : display help message", "h"));
    commands.push_back(CliCommand("load", load_collection,
                                  "load | l <filename> : load collection from <filename>",
                                  "l"));
    commands.push_back(CliCommand("save", save_collection,
                                  "save | s <filename> : save collection to <filename>",
                                  "s"));
    commands.push_back(CliCommand("add-deck", add_deck_to_collection,
                                  "add-deck <deck-name> : add a deck to collection"));
}


int main(int, char **)
{
    string cmd;
    init_cmds(g_cli_commands);
    while(1) {
        getline(cin, cmd);
        if (!process_cmd(cmd, g_cli_commands)) {
            break;
        }
    }
}
