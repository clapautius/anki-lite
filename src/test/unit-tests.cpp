#include <iostream>

#include "cli-utils.hpp"

using namespace std;

bool g_tst_all_tests_ok = true;

#define TST_CHECK_EQUAL(X, Y) { if (X == Y) ; else { std::cout << "Test failed: " << X << "==" << Y << endl << std::endl; g_tst_all_tests_ok = false; } }

void cli_tests()
{
    // CLI unit tests
    vector<string> tokens;
    tokenize_cmd(" \t\tana are  mere \t. ", tokens);
    TST_CHECK_EQUAL(tokens.size(), 4);
    TST_CHECK_EQUAL(tokens[0], "ana");
    TST_CHECK_EQUAL(tokens[1], "are");
    TST_CHECK_EQUAL(tokens[2], "mere");
    TST_CHECK_EQUAL(tokens[3], ".");
}


int main()
{
    cli_tests();

    if (g_tst_all_tests_ok) {
        cout << "All tests passed." << endl;
        return 0;
    } else {
        return 1;
    }
}
