#include <gtest/gtest.h>
#include "../include/mkdir.h"

TEST(MkdirSuite, makeFolder){
    file_system *fs = initFileSystem(2, 2048000);
    ASSERT_EQ(0, mk_dir(fs, "test"));
    ASSERT_EQ(0, cd(fs, "test"));
    ASSERT_STREQ("/test $ ",currentStatus());
    ASSERT_EQ(0, mk_dir(fs, "test_resources"));
    ASSERT_EQ(-1, mk_dir(fs, "test_resources"));
}