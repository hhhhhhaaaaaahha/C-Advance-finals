#include <gtest/gtest.h>
#include "put.h"
#include "metadata.h"
#include "node.h"
#include "rmdir.h"

TEST(PutSuite, FindFileWhoUsedPuts){
    std::string path_to_file = "./test/test_resources/test_file.txt";
    std::string file_name = "test_file.txt";
    file_system *fs = initFileSystem(2, 2048000);
    node *test_node = put_file(fs, path_to_file.c_str());
    ASSERT_EQ(test_node, fs->current_directory->left_most_child);
    ASSERT_EQ(test_node, find_file(fs, file_name.c_str()));
}

TEST(PutSuite, CheckOpenedNodeTypeFile)
{
    std::string path_to_file = "./test/test_resources/test_file.txt";
    Temp_Inode *inode = (Temp_Inode *)malloc(sizeof(Temp_Inode));
    ASSERT_EQ(0, open_file_for_test(path_to_file.c_str(), inode));
    ASSERT_EQ(TYPE_FILE, inode->metadata->type);
    free(inode);
}

TEST(PutSuite, CheckOpenedNodeTypeFolder)
{
    std::string path_to_folder = "./test/test_resources/test_folder";
    Temp_Inode *inode = (Temp_Inode *)malloc(sizeof(Temp_Inode));

    ASSERT_EQ(0, open_file_for_test(path_to_folder.c_str(), inode));
    ASSERT_EQ(TYPE_DIR, inode->metadata->type);
    free(inode);
}

TEST(PutSuite, CheckFileSize)
{
    std::string path_to_file = "./test/test_resources/test_file.txt";
    Temp_Inode *inode = (Temp_Inode *)malloc(sizeof(Temp_Inode));
    ASSERT_EQ(0, open_file_for_test(path_to_file.c_str(), inode));
    ASSERT_EQ(27, inode->metadata->size);
    free(inode);
}

TEST(PutSuite, CheckReadFileContent)
{
    std::string path_to_file = "./test/test_resources/test_file.txt";
    std::string expected_content = "Hello, this is a test file.";
    Temp_Inode *inode = (Temp_Inode *)malloc(sizeof(Temp_Inode));
    ASSERT_EQ(0, open_file_for_test(path_to_file.c_str(), inode));
    ASSERT_EQ(expected_content, std::string(inode->content));
    free(inode);
}

TEST(PutSuite, RealInodeTestFileSize)
{
    std::string path_to_file = "./test/test_resources/test_file.txt";
    file_system *fs = initFileSystem(2, 2048000);
    node *test_node = put_file(fs, path_to_file.c_str());

    ASSERT_EQ(test_node, fs->root->left_most_child);
    ASSERT_EQ(27, test_node->file_info->file_size);
    ASSERT_EQ(std::string(test_node->name), "test_file.txt");

    // TODO: free file_system memory space
    // freeFileSystem(fs);
    free(test_node);
    free(fs);
}


TEST(PutSuite, RealInodeTestFileName)
{
    std::string path_to_file = "./test/test_resources/test_file.txt";
    std::string file_name = "test_file.txt";
    file_system *fs = initFileSystem(2, 2048000);
    node *test_node = put_file(fs, path_to_file.c_str());

    ASSERT_EQ(test_node, fs->root->left_most_child);
    ASSERT_EQ(std::string(test_node->name), file_name);

    test_node = fs->current_directory->left_most_child;
    ASSERT_EQ(file_name, std::string(test_node->name));
    // TODO: free file_system memory space
    // freeFileSystem(fs);
    free(test_node);
    free(fs);
}

