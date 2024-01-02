#include <gtest/gtest.h>
#include "../include/help.h"

// Test the help function to ensure it prints the correct command list
TEST(HelpSuite, PrintHelp) {
    // Capture the output printed to stdout
    testing::internal::CaptureStdout();
    help();
    std::string output = testing::internal::GetCapturedStdout();

    // Construct the expected output string based on the commands available
    std::string expected_output = "\nList of commands\n"
                                  "'ls' list directory\n"
                                  "'cd' change directory\n"
                                  // ... include all the commands listed in the help function
                                  "'exit and store img'\n\n";

    ASSERT_EQ(output, expected_output);
}
