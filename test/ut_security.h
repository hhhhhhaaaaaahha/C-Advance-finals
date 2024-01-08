#include <gtest/gtest.h>
#include "security.h"
#include <string>
#include <cstring>

TEST(Security, test1)
{
    std::string str = "hello";
    std::string psw = "123";
    char buf[100];
    std::string expected_output = "hello";
    encodeWithPassword((char *)str.c_str(), buf, strlen(str.c_str()) + 1, (char *)psw.c_str());
    // printf("%s\n", buf);
    decodeWithPassword(buf, buf, strlen(str.c_str()) + 1, (char *)psw.c_str());
    std::string actual_output = buf;
    EXPECT_EQ(expected_output, actual_output);
}

TEST(Security, securityOnFile)
{
    char * file_name = "./test/test_resources/test_file.txt";
    std::string psw = "123";
    std::string expected_output = "Hello, this is a test file.";

    encodeFile(file_name, (char *)psw.c_str());
    decodeFile(file_name, (char *)psw.c_str());
    char buf[100];
    FILE *fp = fopen(file_name, "r");
    fgets(buf, 100, fp);
    fclose(fp);
    std::string actual_output = buf;
    EXPECT_EQ(expected_output, actual_output);
}