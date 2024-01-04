#include <gtest/gtest.h>
#include "rmdir.h"
#include "node.h"
#include "fs.h"
#include "ls.h"
#include "util.h"
#include <string>

TEST(RmdirSuite, WeirdFileDeleteProblem){
    file_system *fs = initFileSystem(2, 2048000);
    node *folder1 = createFile(fs, fs->current_directory, std::string("folder1").c_str(), TYPE_DIR);
    node *folder2 = createFile(fs, fs->current_directory, std::string("folder2").c_str(), TYPE_DIR);
    ASSERT_STREQ("folder1\nfolder2\n",lsPrint(fs->current_directory));
    node *file1 = createFile(fs, folder1, std::string("file1").c_str(), TYPE_FILE);
    node *file2 = createFile(fs, folder1, std::string("file2").c_str(), TYPE_FILE);
    node *file3 = createFile(fs, folder2, std::string("file3").c_str(), TYPE_FILE);
    node *file4 = createFile(fs, folder2, std::string("file4").c_str(), TYPE_FILE);
    ASSERT_STREQ("file1\nfile2\n",lsPrint(folder1));
    ASSERT_STREQ("file3\nfile4\n",lsPrint(folder2));
    rm_dir(fs, std::string("folder1").c_str());
    ASSERT_STREQ("folder2\n",lsPrint(fs->current_directory));
    free(folder2);
    free(file3);
    free(file4);
    free(fs);
}

TEST(RmdirSuite, FindFolderCheck){
    file_system *fs = initFileSystem(2, 2048000);
    node *folder = createFile(fs, fs->current_directory, std::string("Picture").c_str(), TYPE_DIR);
    node *folder2 = find_dir(fs, std::string("Picture").c_str());
    ASSERT_EQ(folder, folder2);
    free(fs);
    free(folder);
}

TEST(RmdirSuite, FindFileCheck){
    file_system *fs = initFileSystem(2, 2048000);
    node *folder = createFile(fs, fs->current_directory, std::string("Picture").c_str(), TYPE_DIR);
    node *file1 = createFile(fs, folder, std::string("test123.png").c_str(), TYPE_FILE);
    createFile(fs, folder, std::string("test456.png").c_str(), TYPE_FILE);
    node *file3 = find_file(fs, std::string("test123.png").c_str());
    ASSERT_EQ(file1, file3);
}

TEST(RmdirSuite, CheckRmdirRelativePath)
{
    file_system *fs = initFileSystem(2, 2048000);
    createFile(fs, fs->current_directory, std::string("Picture").c_str(), TYPE_DIR);
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

TEST(RmdirSuite, CheckRmMultipleFilesInFolderCase){
    file_system *fs = initFileSystem(2, 2048000);
    node *folder = createFile(fs, fs->current_directory, std::string("Picture").c_str(), TYPE_DIR);
    node *file1 = createFile(fs, folder, std::string("test123.png").c_str(), TYPE_FILE);
    node *file2 = createFile(fs, folder, std::string("test456.png").c_str(), TYPE_FILE);
    ASSERT_STREQ("Picture\n",lsPrint(fs->current_directory));
    rm_dir(fs, std::string("Picture").c_str());
    node *folder2 = find_dir(fs, std::string("Picture").c_str());
    ASSERT_TRUE(folder2 == NULL);
    ASSERT_EQ(NULL,lsPrint(fs->current_directory));
}

TEST(RmdirSuite, CheckRmShouldNotDeleteFile){
    file_system *fs = initFileSystem(2, 2048000);
    node *folder = createFile(fs, fs->current_directory, std::string("Picture").c_str(), TYPE_DIR);
    node *file1 = createFile(fs, folder, std::string("test123.png").c_str(), TYPE_FILE);
    node *file2 = createFile(fs, folder, std::string("test456.png").c_str(), TYPE_FILE);
    int ret = rm_dir(fs, std::string("file1").c_str());
    ASSERT_TRUE(ret == -1); //file not found
    node *file1_1 = find_dir(fs, std::string("file1").c_str());
    ASSERT_TRUE(file1_1 == NULL);
}