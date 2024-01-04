#include <gtest/gtest.h>
#include "../include/fs.h"
#include "../include/status.h"

// Test the print_status function for a file system with known values
// TEST(StatusSuite, PrintStatus) {
//     file_system fs;  // Set up your file system here with known values

//     // Capture the output printed to stdout
//     testing::internal::CaptureStdout();
//     print_status(&fs, fs.root);
//     std::string output = testing::internal::GetCapturedStdout();

//     // Construct the expected output string based on the known values of your file system
//     std::string expected_output = "particion size: known_value\n"
//                                   "total inodes: known_value\n"
//                                   "used inodes: known_value\n"
//                                   "total blocks: known_value\n"
//                                   "used blocks: known_value\n"
//                                   "files' block: known_value\n"
//                                   "block size: known_value\n"
//                                   "free space: known_value\n";

//     ASSERT_EQ(output, expected_output);
// }

TEST(StatusSuite, PrintStatus)
{
    file_system *fs = initFileSystem(2, 2048000);
    // Capture the output printed to stdout
    testing::internal::CaptureStdout();
    print_status(fs, fs->root);
    std::string output = testing::internal::GetCapturedStdout();

    // Construct the expected output string based on the known values of your file system
    std::string expected_output = "\n"
                                  "particion size: 2048000\n"
                                  "total inodes: 500\n"
                                  "used inodes: 1\n"
                                  "total blocks: 500\n"
                                  "used blocks: 1\n"
                                  "files' block: 0\n"
                                  "block size: 4096\n"
                                  "free space: 2043904\n";

    ASSERT_EQ(output, expected_output);
}