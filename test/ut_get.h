#include "get.h"
#include "put.h"
#include "gtest/gtest.h"
#include <string>
#include "fs.h"
#include "node.h"

TEST(GetSuite, CreateDumpFolder)
{
    ASSERT_EQ(0, create_dump_folder());
}

TEST(GetSuite, GetFileFromSystem)
{
    std::string path_to_file = "./test/test_resources/test_file.txt";
    std::string file_name = "test_file.txt";
    file_system *fs = initFileSystem(2, 2048000);
    put_file(fs, path_to_file.c_str());
    ASSERT_EQ(0, get_file(fs, file_name.c_str()));
}

TEST(GetSuite, GetMultiFileFromSystem)
{
    std::string path_to_file1 = "./test/test_resources/test_file.txt";
    std::string path_to_file2 = "./test/test_resources/test_folder/dummy.txt";
    std::string file1_name = "test_file.txt";
    std::string file2_name = "dummy.txt";
    file_system *fs = initFileSystem(2, 2048000);
    node *test_node = put_file(fs, path_to_file1.c_str());
    test_node = put_file(fs, path_to_file2.c_str());
    ASSERT_EQ(0, get_file(fs, file1_name.c_str()));
    ASSERT_EQ(0, get_file(fs, file2_name.c_str()));
}