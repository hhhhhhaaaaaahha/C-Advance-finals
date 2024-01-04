#include <gtest/gtest.h>

#include "ut_fs.h"
#include "ut_get.h"
#include "ut_put.h"
#include "ut_rmdir.h"
#include "ut_cat.h"
#include "ut_help.h"
#include "ut_status.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
