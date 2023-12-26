#include <gtest/gtest.h>

#include "../include/fs.h"

TEST(FileSystemSuite, initialize)
{
    file_system *fs = initFileSystem();
    ASSERT_TRUE(fs != NULL);
}