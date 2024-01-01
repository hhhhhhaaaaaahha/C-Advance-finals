#include <gtest/gtest.h>

#include "../include/fs.h"
#include "../include/ls.h"

TEST(LsSuite, lsAll){
    file_system *fs = initFileSystem(2, 2048000);
    //將folder1, file1.txt加入fs所在directory之下
    createFile(fs, fs->current_directory, std::string("folder1").c_str(), TYPE_DIR);
    createFile(fs, fs->current_directory, std::string("file1.txt").c_str(), TYPE_FILE);
    //以fs所在directory作為欲遍歷的資料夾
    ASSERT_STREQ("folder1\nfile1.txt\n",lsPrint(fs->current_directory));
}