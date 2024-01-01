#include "get.h"

TEST(GetSuite, CreateDumpFolder)
{
    ASSERT_EQ(0, create_dump_folder());
}