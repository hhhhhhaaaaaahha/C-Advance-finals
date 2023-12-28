#include <gtest/gtest.h>
#include <string>
#include <sstream>

#include "../include/fs.h"
#include "../include/node.h"

TEST(FileSystemSuite, CreateNewFileSystem)
{
    file_system *fs = initFileSystem(2, 2048000);
    node *root = fs->root;

    ASSERT_TRUE(fs != nullptr);
    ASSERT_TRUE(root != nullptr);
    ASSERT_EQ(fs->partition_size, 2048000);

    ASSERT_EQ(std::string(root->name), "/");
    ASSERT_TRUE(root->left_most_child == nullptr);
    ASSERT_TRUE(root->sibling == nullptr);

    ASSERT_EQ(fs->num_used_inodes, 1);
    ASSERT_EQ(fs->inode_bitmap[0], 1);
    ASSERT_EQ(fs->inode_bitmap[1], 0);

    ASSERT_EQ(fs->num_used_blocks, 1);
    ASSERT_EQ(fs->data_bitmap[0], 1);
    ASSERT_EQ(fs->data_bitmap[1], 0);
}

TEST(FileSystemSuite, DeleteRootNode)
{
    testing::internal::CaptureStdout();

    file_system *fs = initFileSystem(2, 2048000);
    deleteFile(fs, fs->root);

    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Cannot delete root!!!\n");
}

TEST(FileSystemSuite, CreateFile)
{
    file_system *fs = initFileSystem(2, 2048000);
    node *test_123 = createFile(fs, fs->current_directory, std::string("test123.txt").c_str(), TYPE_FILE);

    ASSERT_EQ(test_123, fs->root->left_most_child);

    ASSERT_EQ(test_123->inode, 1);
    ASSERT_EQ(std::string(test_123->name), "test123.txt");

    ASSERT_EQ(test_123->parent, fs->root);
    ASSERT_EQ(test_123->left_most_child, nullptr);
    ASSERT_EQ(test_123->sibling, nullptr);

    node *test_456 = createFile(fs, fs->current_directory, std::string("test456.txt").c_str(), TYPE_FILE);

    ASSERT_EQ(test_456->inode, 2);
    ASSERT_EQ(std::string(test_456->name), "test456.txt");

    ASSERT_EQ(test_456->parent, fs->root);
    ASSERT_EQ(test_456, test_123->sibling);
    ASSERT_EQ(test_456->sibling, nullptr);
}

TEST(FileSystemSuite, CreateFolder)
{
    file_system *fs = initFileSystem(2, 2048000);
    node *folder = createFile(fs, fs->current_directory, std::string("Picture").c_str(), TYPE_DIR);
    ASSERT_EQ(folder, fs->root->left_most_child);
    ASSERT_EQ(folder->sibling, nullptr);

    node *test_123 = createFile(fs, folder, std::string("test123.png").c_str(), TYPE_FILE);
    ASSERT_EQ(test_123, folder->left_most_child);
    ASSERT_EQ(test_123->sibling, nullptr);
    ASSERT_EQ(folder, test_123->parent);

    node *folder_2 = createFile(fs, folder, std::string("2023_Picture").c_str(), TYPE_DIR);
    ASSERT_EQ(folder_2, test_123->sibling);
    ASSERT_EQ(folder_2->sibling, nullptr);
    ASSERT_EQ(folder, folder_2->parent);
}

TEST(FileSystemSuite, DeleteFile)
{
}