// test.cpp

#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>

#include "../Argparser.h"

class ArgumentParserTest : public ::testing::Test {
protected:

    void SetUp() override {
    }

    void TearDown() override {
        // Clean-up code, if needed
    }
};

// Test integer argument parsing
TEST_F(ArgumentParserTest, ParsesIntegerArgument) {

     // Define the number of mock arguments
    int mock_argc = 3;

    // Create a mock argv array with sample command-line arguments
    char arg0[] = "program.cpp";      // Simulate the program name
    char arg1[] = "-a";
    char arg2[] = "36";

    // Create an array of char* pointers, each pointing to one of the arguments
    char* mock_argv[] = { arg0, arg1, arg2};

    // create parser object
    Argparser parser(mock_argc, mock_argv);
    
    // add_option (flag = a, args_allowed = true, required = true, max_if_args = 1, min_if_args = 1);
    parser.add_option ('a', true, true, 1, 1);

    // run parser
    parser.parse();

    // check that it got 36 for -a flag
    std::vector<int> results = parser.get_values_int('a');

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results.at(0), 36);
}

// Test string argument parsing
TEST_F(ArgumentParserTest, ParsesStringArgument) {

     // Define the number of mock arguments
    int mock_argc = 3;

    // Create a mock argv array with sample command-line arguments
    char arg0[] = "program.cpp";      // Simulate the program name
    char arg1[] = "-a";
    char arg2[] = "TEST_VALUE";

    // Create an array of char* pointers, each pointing to one of the arguments
    char* mock_argv[] = { arg0, arg1, arg2};

    // create parser object
    Argparser parser(mock_argc, mock_argv);
    
    // add_option (flag = a, args_allowed = true, required = true, max_if_args = 1, min_if_args = 1);
    parser.add_option ('a', true, true, 1, 1);

    // run parser
    parser.parse();

    // check that it got expected result
    std::vector<std::string> results = parser.get_values_string('a');

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results.at(0), "TEST_VALUE");
}

// Test integer argument parsing
TEST_F(ArgumentParserTest, ParsesManyIntegerArgument) {

     // Define the number of mock arguments
    int mock_argc = 3;

    // Create a mock argv array with sample command-line arguments
    char arg0[] = "program.cpp";      // Simulate the program name
    char arg1[] = "-a";
    char arg2[] = "36";
    char arg3[] = "-b";
    char arg4[] = "100";
    char arg5[] = "73";
    char arg6[] = "78";
    char arg7[] = "56";
    char arg8[] = "-c";
    char arg9[] = "13";
    char arg10[] = "67";

    // Create an array of char* pointers, each pointing to one of the arguments
    char* mock_argv[] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10};

    Argparser parser(mock_argc, mock_argv);
    
    // add_option (flag = a, args_allowed = true, required = true, max_if_args = 1, min_if_args = 1);
    parser.add_option ('a', true, true, 10, 1);

    // add_option (flag = a, args_allowed = true, required = true, max_if_args = 1, min_if_args = 1);
    parser.add_option ('b', true, true, 10, 1);

    // add_option (flag = a, args_allowed = true, required = true, max_if_args = 1, min_if_args = 1);
    parser.add_option ('c', true, true, 10, 1);

    // run parser
    parser.parse();

    std::vector<int> results_a = parser.get_values_int('a');
    std::vector<int> results_b = parser.get_values_int('b');
    std::vector<int> results_c = parser.get_values_int('c');

    EXPECT_EQ(results_a.size(), 1);
    EXPECT_EQ(results_a.at(0), 36);

    EXPECT_EQ(results_b.size(), 4);
    EXPECT_EQ(results_b.at(0), 100);
    EXPECT_EQ(results_b.at(0), 73);
    EXPECT_EQ(results_b.at(0), 78);
    EXPECT_EQ(results_b.at(0), 56);

    EXPECT_EQ(results_c.size(), 2);
    EXPECT_EQ(results_c.at(0), 13);
    EXPECT_EQ(results_c.at(0), 67);
}

// Test missing required argument
TEST_F(ArgumentParserTest, ThrowsOnMissingRequiredArgument) {

     // Define the number of mock arguments
    int mock_argc = 3;

    // Create a mock argv array with sample command-line arguments
    char arg0[] = "program.cpp";      // Simulate the program name
    char arg1[] = "-a";
    char arg2[] = "36";

    // Create an array of char* pointers, each pointing to one of the arguments
    char* mock_argv[] = { arg0, arg1, arg2};

    // create parser object
    Argparser parser_a(mock_argc, mock_argv);
    Argparser parser_b(mock_argc, mock_argv);
    
    // testing different variations of a required argument

    // add_option (flag = a, args_allowed = true, required = true, max_if_args = 1, min_if_args = 1);
    parser_a.add_option ('a', true, true, 1, 1);

    // add_option (flag = a, args_allowed = false, required = true, max_if_args = 1, min_if_args = 1);
    parser_b.add_option ('b', false, true, 1, 1);

    EXPECT_THROW({
        parser_a.parse();
    }, std::invalid_argument);
}

// Test handling unknown argument
TEST_F(ArgumentParserTest, ThrowsOnUnknownArgument) {

     // Define the number of mock arguments
    int mock_argc = 3;

    // Create a mock argv array with sample command-line arguments
    char arg0[] = "program.cpp";      // Simulate the program name
    char arg1[] = "-a";
    char arg2[] = "36";
    char arg3[] = "-b";
    char arg4[] = "100";
    char arg5[] = "73";
    char arg6[] = "78";
    char arg7[] = "56";
    char arg8[] = "-c";
    char arg9[] = "13";
    char arg10[] = "67";

    // Create an array of char* pointers, each pointing to one of the arguments
    char* mock_argv[] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10};

    // create parser object
    Argparser parser(mock_argc, mock_argv);
    
    // add_option (flag = a, args_allowed = true, required = true, max_if_args = 1, min_if_args = 1);
    parser.add_option ('a', true, true, 10, 1);

    // add_option (flag = a, args_allowed = true, required = true, max_if_args = 1, min_if_args = 1);
    parser.add_option ('b', true, true, 10, 1);

    // add_option (flag = a, args_allowed = true, required = true, max_if_args = 1, min_if_args = 1);
    parser.add_option ('x', true, true, 10, 1);

    EXPECT_THROW({
        parser.parse();
    }, std::invalid_argument);
}
