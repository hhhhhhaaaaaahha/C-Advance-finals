#include "../include/put.h"
#include "../include/inode.h"


TEST(PutSuite, CheckOpenedNodeTypeFile)
{
    std::string path_to_file = "./test/test_resources/test_file.txt";
    Temp_Inode * inode = (Temp_Inode*)malloc(sizeof(Temp_Inode));
    ASSERT_EQ(0, open_file(path_to_file.c_str(), inode));
    ASSERT_EQ(TYPE_FILE, inode->metadata->type);
    free(inode);
}


TEST(PutSuite, CheckOpenedNodeTypeFolder)
{
    std::string path_to_folder = "./test/test_resources/test_folder";
    Temp_Inode * inode = (Temp_Inode*)malloc(sizeof(Temp_Inode));

    ASSERT_EQ(0, open_file(path_to_folder.c_str(), inode));
    ASSERT_EQ(TYPE_DIR, inode->metadata->type);
    free(inode);
}

TEST(PutSuite, CheckFileSize){
    std::string path_to_file = "./test/test_resources/test_file.txt";
    Temp_Inode * inode = (Temp_Inode*)malloc(sizeof(Temp_Inode));
    ASSERT_EQ(0, open_file(path_to_file.c_str(), inode));
    ASSERT_EQ(27, inode->metadata->size);
    free(inode);
}

TEST(PutSuite, CheckReadFileContent){
    std::string path_to_file = "./test/test_resources/test_file.txt";
    std::string expected_content = "Hello, this is a test file.";
    Temp_Inode * inode = (Temp_Inode*)malloc(sizeof(Temp_Inode));
    ASSERT_EQ(0, open_file(path_to_file.c_str(), inode));
    ASSERT_EQ(expected_content, std::string(inode->content));
    free(inode);
}

