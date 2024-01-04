#include <gtest/gtest.h>
#include "dump.h"
#include "fs.h"
#include "node.h"
#include <string>
#include <fstream>

TEST(DumpSuite, DumpFile)
{
    // create file system
    file_system *fs = initFileSystem(2, 2048000);
    // call the dump function
    std::string dump_file_name = "dump_test";
    // dump() should record the whole file system in a file called dump_test
    dump(fs, dump_file_name.c_str());
    dump_file_name = "dump_test.dump";
    // check that the file was created
    std::ifstream dump_file(dump_file_name.c_str());
    ASSERT_TRUE(dump_file.good());
    // the content should be according to the filesystem structure and node structure
    // check that the file has the correct content in json format
    std::string expected_output = "{\n"
                                  "\t\"partition_size\": 2048000,\n"
                                  "\t\"total_inodes\": 500,\n"
                                  "\t\"used_inodes\": 1,\n"
                                  "\t\"total_blocks\": 500,\n"
                                  "\t\"used_blocks\": 1,\n"
                                  "\t\"files_block\": 0,\n"
                                  "\t\"block_size\": 4096,\n"
                                  "\t\"free_space\": 2043904,\n"
                                  "\t\"root\": {\n"
                                  "\t\t\"name\": \"/\",\n"
                                  "\t\t\"type\": \"dir\",\n"
                                  "\t\t\"size\": 2048,\n"
                                  "\t\t\"blocks\": 1,\n"
                                  "\t\t\"parent\": null,\n"
                                  "\t\t\"children\": []\n"
                                  "\t}\n"
                                  "}\n";

    // check the content of the file
    std::string dump_file_content((std::istreambuf_iterator<char>(dump_file)),
                                  std::istreambuf_iterator<char>());    
    ASSERT_EQ(dump_file_content, expected_output);
    // remove the file
    remove(dump_file_name.c_str());
    // free the file system
    free(fs);
}

