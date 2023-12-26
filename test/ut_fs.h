#include <gtest/gtest.h>

#include "../src/fs.h"

TEST(FileSystemSuite, initialize)
{
    file_system *fs = initFileSystem();
    ASSERT_TRUE(fs != NULL);
}