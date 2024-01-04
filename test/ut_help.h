#include <gtest/gtest.h>
#include "../include/help.h"

// Test the help function to ensure it prints the correct command list
TEST(HelpSuite, PrintHelp)
{
    // Capture the output printed to stdout
    testing::internal::CaptureStdout();
    help();
    std::string output = testing::internal::GetCapturedStdout();

    // Construct the expected output string based on the commands available
    std::string expected_output = "\nList of commands\n"
                                  "'ls' list directory\n"
                                  "'cd' change directory\n"
                                  "'rm' remove\n"
                                  "'mkdir' make directory\n"
                                  "'rmdir' remove directory\n"
                                  "'put' put file into the space\n"
                                  "'get' get file from the space\n"
                                  "'cat' show content\n"
                                  "'status' show status of the space\n"
                                  "'help'\n"
                                  "'exit and store img'\n"
                                  "\n";

    ASSERT_EQ(output, expected_output);
}
