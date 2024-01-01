#include <gtest/gtest.h>
#include "rmdir.h"
#include "node.h"
#include "fs.h"
#include <string>

TEST(RmdirSuite, FindFolderCheck){
    file_system *fs = initFileSystem(2, 2048000);
    node *folder = createFile(fs, fs->current_directory, std::string("Picture").c_str(), TYPE_DIR);
    node *folder2 = find_dir(fs, std::string("Picture").c_str());
    ASSERT_EQ(folder, folder2);
}

TEST(RmdirSuite, FindFileCheck){
    file_system *fs = initFileSystem(2, 2048000);
    node *folder = createFile(fs, fs->current_directory, std::string("Picture").c_str(), TYPE_DIR);
    node *file1 = createFile(fs, folder, std::string("test123.png").c_str(), TYPE_FILE);
    node *file2 = createFile(fs, folder, std::string("test456.png").c_str(), TYPE_FILE);
    node *file3 = find_file(fs, std::string("test123.png").c_str());
    ASSERT_EQ(file1, file3);
}

TEST(RmdirSuite, CheckRmdirRelativePath)
{
    file_system *fs = initFileSystem(2, 2048000);
    node *folder = createFile(fs, fs->current_directory, std::string("Picture").c_str(), TYPE_DIR);
    rm_dir(fs, std::string("Picture").c_str());
    node *folder2 = find_dir(fs, std::string("Picture").c_str());
    ASSERT_TRUE(folder2 == NULL);
}

TEST(RmdirSuite, CheckRmMultipleFilesInFolder){
    file_system *fs = initFileSystem(2, 2048000);
    node *folder = createFile(fs, fs->current_directory, std::string("Picture").c_str(), TYPE_DIR);
    node *file1 = createFile(fs, folder, std::string("test123.png").c_str(), TYPE_FILE);
    node *file2 = createFile(fs, folder, std::string("test456.png").c_str(), TYPE_FILE);
    rm_dir(fs, std::string("Picture").c_str());
    node *folder2 = find_dir(fs, std::string("Picture").c_str());
    ASSERT_TRUE(folder2 == NULL);
}
