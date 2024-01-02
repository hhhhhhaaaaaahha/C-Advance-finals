#include <gtest/gtest.h>
#include "../include/fs.h"
#include "../include/node.h"
#include "../include/cat.h"
#include <fstream>
#include <iostream>

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

// Test the find_and_print function with a directory
TEST(CatSuite, CatFile) {
    std::string path_to_file1 = "./test/test_resources/test_file.txt";
    std::string file1_name = "test_file.txt";
    file_system *fs = initFileSystem(2, 2048000);
    node *test_node = put_file(fs, path_to_file1.c_str());

    // Capture the output printed to stdout
    testing::internal::CaptureStdout();
    find_and_print(fs, file1_name.c_str());
    std::string output = testing::internal::GetCapturedStdout();

    // get expected output
    std::ifstream t("./test/test_resources/test_file.txt");
    std::string expected_output((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

    // Check that the output matches the expected file content
    ASSERT_EQ(output, expected_output);
}

// Test the find_and_print function with a non-existent file
// TEST(CatSuite, HandlesNonexistentFile) {
//     file_system fs;  // Set up your file system here
//     const char* filename = "nonexistent.txt";

//     testing::internal::CaptureStdout();
//     find_and_print(&fs, filename);
//     std::string output = testing::internal::GetCapturedStdout();

//     ASSERT_EQ(output, "File not found or is not a regular file.\n");
// }

TEST(CatSuite, CatFileNotExist) {
    std::string path_to_file1 = "./test/test_resources/test_file.txt";
    std::string file1_name = "test_file.txt";
    std::string wrong_file_name = "wrong_file.txt";
    file_system *fs = initFileSystem(2, 2048000);
    node *test_node = put_file(fs, path_to_file1.c_str());

    // Capture the output printed to stdout
    testing::internal::CaptureStdout();
    find_and_print(fs, wrong_file_name.c_str());
    std::string output = testing::internal::GetCapturedStdout();

    // get expected output
    std::string expected_output("File not found or is not a regular file.\n");

    // Check that the output matches the expected file content
    ASSERT_EQ(output, expected_output);
}