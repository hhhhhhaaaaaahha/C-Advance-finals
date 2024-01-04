#include <gtest/gtest.h>

#include "../include/cd.h"

//cd directory
TEST(CdSuite, cdDirectory){
    file_system *fs = initFileSystem(2, 2048000);
    node *test = createFile(fs, fs->current_directory, std::string("test").c_str(), TYPE_DIR);
    node *test_resources = createFile(fs, test, std::string("test_resources").c_str(), TYPE_DIR);
    node *test_folder = createFile(fs, test_resources, std::string("test_folder").c_str(), TYPE_DIR);
    cd(fs, "test");
    ASSERT_STREQ("/test $ ",currentStatus());
    cd(fs, "test_resources");
    ASSERT_STREQ("/test/test_resources $ ",currentStatus());
    cd(fs, "test_folder");
    ASSERT_STREQ("/test/test_resources/test_folder $ ",currentStatus());
}

//cd ..
TEST(CdSuite, cdPrevDirectory){
    file_system *fs = initFileSystem(2, 2048000);
    node *test = createFile(fs, fs->current_directory, std::string("test").c_str(), TYPE_DIR);
    node *test_resources = createFile(fs, test, std::string("test_resources").c_str(), TYPE_DIR);
    node *test_folder = createFile(fs, test_resources, std::string("test_folder").c_str(), TYPE_DIR);
    cd(fs, "test");
    ASSERT_STREQ("/test $ ",currentStatus());
    cd(fs, "test_resources");
    ASSERT_STREQ("/test/test_resources $ ",currentStatus());
    cd(fs, "..");
    ASSERT_STREQ("/test $ ",currentStatus());
}

//cd /
TEST(CdSuite, cdRoot){
    file_system *fs = initFileSystem(2, 2048000);
    node *test = createFile(fs, fs->current_directory, std::string("test").c_str(), TYPE_DIR);
    node *test_resources = createFile(fs, test, std::string("test_resources").c_str(), TYPE_DIR);
    node *test_folder = createFile(fs, test_resources, std::string("test_folder").c_str(), TYPE_DIR);
    cd(fs, "test");
    ASSERT_STREQ("/test $ ",currentStatus());
    cd(fs, "test_resources");
    ASSERT_STREQ("/test/test_resources $ ",currentStatus());
    cd(fs, "/");
    ASSERT_STREQ("/ $ ",currentStatus());
}
