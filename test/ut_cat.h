#include <gtest/gtest.h>
#include "../include/fs.h"
#include "../include/node.h"
#include "../include/cat.h"

// Test the find_and_print function with an existing file
// TEST(CatSuite, HandlesExistingFile) {
//     file_system fs;  // Set up your file system here
//     const char* filename = "existing.txt";  // Ensure this file exists in your mock file system
//     // TODO: init the fs
//     // here
//     EXPECT_TRUE(&fs!=NULL);

//     // Capture the output printed to stdout
//     testing::internal::CaptureStdout();
//     find_and_print(&fs, filename);
//     std::string output = testing::internal::GetCapturedStdout();

//     // Check that the output matches the expected file content
//     ASSERT_EQ(output, "Expected content of existing.txt\n");
// }

// Test the find_and_print function with a non-existent file
// TEST(CatSuite, HandlesNonexistentFile) {
//     file_system fs;  // Set up your file system here
//     const char* filename = "nonexistent.txt";

//     testing::internal::CaptureStdout();
//     find_and_print(&fs, filename);
//     std::string output = testing::internal::GetCapturedStdout();

//     ASSERT_EQ(output, "File not found or is not a regular file.\n");
// }
