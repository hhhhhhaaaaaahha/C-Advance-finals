#include <gtest/gtest.h>
#include "restore.h"
#include "dump.h"
#include "fs.h"
#include "node.h"

TEST(RestoreSuite, RestoreFromFileOnlyFS){
    // create file system
    file_system *fs = initFileSystem(2, 2048000);
    // call the dump function
    std::string dump_file_name = "dump_test";
    // dump() should record the whole file system in a file called dump_test
    dump(fs, dump_file_name.c_str());
    dump_file_name = "dump_test.dump";

    // restore the file system
    file_system *fs2 = restore(dump_file_name.c_str());
    // check that the file system was restored correctly
    ASSERT_FALSE(fs2 == NULL);
    ASSERT_EQ(fs->partition_size, fs2->partition_size);
    ASSERT_EQ(fs->num_total_blocks, fs2->num_total_blocks);
    ASSERT_EQ(fs->num_used_inodes, fs2->num_used_inodes);
    ASSERT_EQ(fs->num_used_blocks, fs2->num_used_blocks);
    // remove the file
    remove(dump_file_name.c_str());
    // free the file system
    free(fs);
    free(fs2);
}

TEST(RestoreSuite, RestoreFromFileOneFile){
    // create file system
    file_system *fs = initFileSystem(2, 2048000);
    // create file
    std::string file_name = "test_file.txt";
    node *file = createFile(fs, fs->current_directory, file_name.c_str(), TYPE_FILE);
    // call the dump function
    std::string dump_file_name = "dump_test";
    // dump() should record the whole file system in a file called dump_test
    dump(fs, dump_file_name.c_str());
    dump_file_name = "dump_test.dump";

    // restore the file system
    file_system *fs2 = restore(dump_file_name.c_str());
    // check that the file system was restored correctly
    ASSERT_FALSE(fs2 == NULL);
    node * fs1_file = fs->root->left_most_child;
    node * fs2_file = fs2->root->left_most_child;
    ASSERT_STREQ(fs1_file->name, fs2_file->name);
    ASSERT_EQ(fs1_file->file_info->file_size, fs2_file->file_info->file_size);
    ASSERT_EQ(fs1_file->file_info->node_type, fs2_file->file_info->node_type);
    ASSERT_EQ(fs1_file->file_info->num_used_blocks, fs2_file->file_info->num_used_blocks);
    ASSERT_EQ(fs1_file->file_info->first_data_block->data, fs2_file->file_info->first_data_block->data);

    // remove the file
    remove(dump_file_name.c_str());
    // free the file system
    free(fs);
    free(fs2);
}