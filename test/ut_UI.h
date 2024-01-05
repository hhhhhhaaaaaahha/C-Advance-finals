#include "fake_terminal.h"
#include "fs.h"
#include "node.h"
#include "put.h"

TEST(UISuite, MainLoopInAndOut)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "exit";
    std::string output = "Goodbye!\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_PROCESS);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
}

TEST(UISuite, ShowPrefix)
{
    file_system *fs = initFileSystem(2, 2048000);
    testing::internal::CaptureStdout();
    show_prefix(fs);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("/ $ ", output.c_str());
    free(fs);
}

TEST(UISuite, Cat)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "cat";
    std::string output = "Usage: cat <filename>\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, CatNotFound)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "cat file1";
    std::string output = "File not found or is not a regular file.\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_SUCCESS);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, Put)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "put";
    std::string output = "Usage: put <external file path>\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, PutNotFound)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "put file1";
    std::string output = "put: File not found.\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, PutSuccess)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "put ./test/test_resources/test_file.txt";
    std::string output = "put: File put successfully.\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_SUCCESS);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    // check file name
    node *test_node = fs->current_directory->left_most_child;
    ASSERT_EQ(std::string(test_node->name), "test_file.txt");
    // check file size
    ASSERT_EQ(27, test_node->file_info->file_size);
    free(fs);
}

TEST(UISuite, CatRealFile)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "put ./test/test_resources/test_file.txt";
    std::string output = "put: File put successfully.\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    // check file name
    node *test_node = fs->current_directory->left_most_child;
    // check file size
    // cat
    input = "cat test_file.txt";
    // get expected output
    std::ifstream t("./test/test_resources/test_file.txt");
    std::string expected_output((std::istreambuf_iterator<char>(t)),
                                std::istreambuf_iterator<char>());

    testing::internal::CaptureStdout();
    ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_SUCCESS);
    output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(expected_output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, Cd)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "cd";
    std::string output = "Usage: cd <directory name>\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, CdNotFound)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "cd dir1";
    std::string output = "Not a exist directory!\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, Mkdir)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "mkdir";
    std::string output = "Usage: mkdir <directory name>\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, MkdirSuccess)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "mkdir dir1";
    std::string output = "mkdir: Directory created successfully.\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_SUCCESS);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    // check file name
    node *test_node = fs->current_directory->left_most_child;
    ASSERT_EQ(std::string(test_node->name), "dir1");
    // check file size
    ASSERT_EQ(FAKE_DIR_SIZE, test_node->file_info->file_size);
    free(fs);
}

TEST(UISuite, MkdirFolderNameExist)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "mkdir dir1";
    std::string output = "mkdir: Directory created successfully.\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    // check file name
    node *test_node = fs->current_directory->left_most_child;
    // check file size
    // mkdir
    input = "mkdir dir1";
    testing::internal::CaptureStdout();
    ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("Folder Exist!\n", output2.c_str());
    free(fs);
}

TEST(UISuite, CdFound)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "mkdir dir1";
    std::string output = "mkdir: Directory created successfully.\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    // check file name
    node *test_node = fs->current_directory->left_most_child;
    // check file size
    // cd
    input = "cd dir1";
    testing::internal::CaptureStdout();
    ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_SUCCESS);
    output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("", output2.c_str());
    ASSERT_EQ(fs->current_directory, test_node);
    free(fs);
}

TEST(UISuite, Get)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "get";
    std::string output = "Usage: get <file name>\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, GetNotFound)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "get file1";
    std::string output = "File not found\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
}

TEST(UISuite, GetSuccess)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "put ./test/test_resources/test_file.txt";
    std::string output = "put: File put successfully.\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    // check file name
    node *test_node = fs->current_directory->left_most_child;
    // check file size
    // get
    input = "get test_file.txt";
    testing::internal::CaptureStdout();
    ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_SUCCESS);
    output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("get: File get successfully.\n", output2.c_str());
    free(fs);
    std::remove("./dump/test_file.txt");
}

TEST(UISuite, Ls)
{
    file_system *fs = initFileSystem(2, 2048000);
    node *node_1 = createFile(fs, fs->current_directory, "test_file.txt", TYPE_FILE);
    std::string input = "ls";
    std::string output = "test_file.txt\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, Rmdir)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "rmdir";
    std::string output = "Usage: rmdir <directory name>\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, RmdirNotFound)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "rmdir dir1";
    std::string output = "No such directory\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, RmdirSuccess)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "mkdir dir1";
    std::string output = "mkdir: Directory created successfully.\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    // check file name
    node *test_node = fs->current_directory->left_most_child;
    // check file size
    // rmdir
    input = "rmdir dir1";
    testing::internal::CaptureStdout();
    ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_SUCCESS);
    output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("rmdir: Directory removed successfully.\n", output2.c_str());
    free(fs);
}

TEST(UISuite, Rm)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "rm";
    std::string output = "Usage: rm <file name>\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, RmNotFound)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "rm file1";
    std::string output = "Not an exist file!\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_EQ(ret, UI_EXIT_FAILURE);
    ASSERT_STREQ(output.c_str(), output2.c_str());
    free(fs);
}

TEST(UISuite, RmSuccess)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "put ./test/test_resources/test_file.txt";
    std::string output = "put: File put successfully.\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    // check file name
    node *test_node = fs->current_directory->left_most_child;
    // check file size
    // rm
    input = "rm test_file.txt";
    testing::internal::CaptureStdout();
    ret = fake_terminal(input.c_str(), fs);
    ASSERT_EQ(ret, UI_EXIT_SUCCESS);
    output2 = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("rm: File removed successfully.\n", output2.c_str());
    free(fs);
}

TEST(UISuite, Status)
{
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "status";
    // Construct the expected output string based on the known values of your file system
    std::string expected_output = "\n"
                                  "particion size: 2048000\n"
                                  "total inodes: 500\n"
                                  "used inodes: 1\n"
                                  "total blocks: 500\n"
                                  "used blocks: 1\n"
                                  "files' block: 0\n"
                                  "block size: 4096\n"
                                  "free space: 2043904\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_EQ(ret, UI_EXIT_SUCCESS);
    ASSERT_STREQ(expected_output.c_str(), output2.c_str());
    free(fs);
}


TEST(UISuite, Help){
    file_system *fs = initFileSystem(2, 2048000);
    std::string input = "help";
    // Construct the expected output string based on the known values of your file system
    std::string expected_output = "\nList of commands\n"
                                  "'ls' list directory\n"
                                  "'cd' change directory\n"
                                  "'rm' remove\n"
                                  "'mkdir' make directory\n"
                                  "'rmdir' remove directory\n"
                                  "'put' put file into the space\n"
                                  "'get' get file from the space\n"
                                  "'cat' show content\n"
                                  "'status' show status of the space\n"
                                  "'help'\n"
                                  "'exit and store img'\n"
                                  "\n";
    testing::internal::CaptureStdout();
    exit_code_t ret = fake_terminal(input.c_str(), fs);
    std::string output2 = testing::internal::GetCapturedStdout();
    ASSERT_EQ(ret, UI_EXIT_SUCCESS);
    ASSERT_STREQ(expected_output.c_str(), output2.c_str());
    free(fs);
}