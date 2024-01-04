#include <gtest/gtest.h>

#include "../include/rm.h"
#include "../include/fs.h"
#include "../include/ls.h"

TEST(RmSuite, RemoveFile){
    file_system *fs1 = initFileSystem(2, 2048000);
    createFile(fs1, fs1->current_directory, std::string("test123.txt").c_str(), TYPE_FILE);
    createFile(fs1, fs1->current_directory, std::string("test456.txt").c_str(), TYPE_FILE);

    ASSERT_STREQ("test123.txt\ntest456.txt\n",lsPrint(fs1->current_directory));
    rm(fs1, "test123.txt");
    node * test123 = find_file(fs1, std::string("test123.txt").c_str());
    ASSERT_TRUE(test123 == NULL);
    ASSERT_STREQ("test456.txt\n",lsPrint(fs1->current_directory));    
}