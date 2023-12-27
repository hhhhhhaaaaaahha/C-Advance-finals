#include <gtest/gtest.h>

#include "ut_fs.h"
#include "ut_get.h"
#include "ut_put.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
