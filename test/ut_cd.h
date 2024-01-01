#include <gtest/gtest.h>

#include "../include/cd.h"

//cd directory
TEST(CdSuite, cdDirectory){
    char  path_to_folder[100] = "./test/test_resources/test_folder";
    cd(path_to_folder);
    ASSERT_STREQ("./test/test_resources/test_folder $ ",currentStatus());
}

TEST(CdSuite, cdNextDirectory){
    char  path_to_folder[100] = "./test/test_resources";  
    char inSide_folder[50] = "test_folder";  
    cd(path_to_folder);
    cd(inSide_folder);
    ASSERT_STREQ("./test/test_resources/test_folder $ ",currentStatus());
}

//cd ..
TEST(CdSuite, cdPrevDirectory){
    char  path_to_folder2[100] = "./test/test_resources/test_folder";
    char operatorDot[3] = "..";
    cd(path_to_folder2);
    cd(operatorDot);
    ASSERT_STREQ("./test/test_resources $ ",currentStatus());
}

//cd /
TEST(CdSuite, cdRoot){
    char  path_to_folder3[100] = "./test/test_resources/test_folder";
    char operatorSlash[3] = "/";
    cd(path_to_folder3);
    cd(operatorSlash);
    ASSERT_STREQ("/ $ ",currentStatus());
}