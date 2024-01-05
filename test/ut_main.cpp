#include <gtest/gtest.h>

#include "ut_fs.h"
#include "ut_get.h"
#include "ut_put.h"
#include "ut_rmdir.h"
#include "ut_cat.h"
#include "ut_help.h"
#include "ut_status.h"
#include "ut_dumpfile.h"
#include "ut_restore.h"
#include "ut_UI.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
