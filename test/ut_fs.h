#include <gtest/gtest.h>
#include <string>

#include "../include/fs.h"
#include "../include/node.h"

TEST(FileSystemSuite, CreateNewFileSystem)
{
    file_system *fs = initFileSystem(2);

    ASSERT_TRUE(fs != nullptr);
    ASSERT_EQ(std::string(fs->root->name), "/");
    ASSERT_TRUE(fs->root->child == nullptr);
    ASSERT_EQ(fs->inode_bitmap[0], 1);
}
