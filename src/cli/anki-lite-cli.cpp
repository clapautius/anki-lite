#include <iostream>
#include <string>
#include <functional>

#include "simple-db.hpp"
#include "cli-utils.hpp"
#include "collection.hpp"
#include "simple-db.hpp"
#include "exceptions.hpp"
#include "anki-utils.hpp"
#include "memo-alg-sm2.hpp"

using namespace std;
using namespace anki_lite;

vector<CliCommand> g_cli_commands;
anki_lite::Collection g_collection;


bool print_help(const string &s="");

bool print_help(const string &)
{
    cout << "Available commands:" << endl;
    for_each (g_cli_commands.begin(), g_cli_commands.end(),
              [] (const CliCommand &c) { cout << " - " << c.help_message() << endl; });
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
        Deck deck(g_collection.get_free_id(), details);
        g_collection.add_deck(deck);
    }
    return true;
}


bool add_card_to_collection(const string &cmd)
{
    vector<string> tokens;
    tokenize_cmd(cmd, tokens);
    if (tokens.size() < 4) {
        cout << "Invalid command" << endl;
    } else {
        Id deck_id = anki_lite::string_to_id(tokens[1]);
        Deck &deck = g_collection.get_deck_by_id(deck_id);
        boost::shared_ptr<Card> card(new Card(g_collection.get_free_id(),
                                              tokens[2], tokens[3]));
        card->set_deck_id(deck_id);
        deck.add_card(card);
    }
    return true;
}


/**
 * Print entire collection to stdout.
 */
bool print_collection(const string&)
{
    cout << g_collection.to_string() << endl;
    return true;
}

/**
 * View the next card (and update its parameters).
 */
bool view_next_card(const string &cmd)
{
    vector<string> tokens;
    int response_quality = 3;
    tokenize_cmd(cmd, tokens);
    /*
    if (tokens.size() > 1) {
        response_quality = string_to_id(tokens[1]);
    }
    */
    // :todo: atm the card is chosen from all decks
    boost::shared_ptr<ICard> card = g_collection.get_next_card();
    cout << card->to_string() << endl;
    std::auto_ptr<anki_lite::IMemoAlg> alg(new anki_lite::MemoAlgSm2);
    do
    {
        cout << "Response quality: ";
        if (!(cin >> response_quality) || (response_quality < 0 || response_quality > 5)){
            string ign;
            cout << "Invalid response (must be a number between 0 and 5)" << endl;
            cin.clear();
            getline(cin, ign);
        } else {
            break;
        }
    } while (1);
    alg->update_viewed_card(*card, response_quality);
    cout << card->to_string() << endl;
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
    commands.push_back(CliCommand("add-card", add_card_to_collection,
                                  "add-card <deck-id> <front-text> <back-text> "
                                  ": add a deck to collection"));
    commands.push_back(CliCommand("print", print_collection,
                                  "print | p : print collection to stdout", "p"));
    commands.push_back(CliCommand("view-next-card", view_next_card,
                                  "view-next-card | view [ <response-quality: 0-5> ] : "
                                  "view the next due card and update its parameters",
                                  "view"));
}


int main(int, char **)
{
    string cmd;
    init_cmds(g_cli_commands);
    while(1) {
        cout << "> ";
        getline(cin, cmd);
        if (!process_cmd(cmd, g_cli_commands)) {
            break;
        }
    }
}
