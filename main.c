#include "include/metadata.h"
#include "include/fs.h"
#include "restore.h"

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int mode = 0;
    while (!(mode == 1 || mode == 2))
    {
        printf("Options:\n");
        printf("\t1. Loads file system from file\n");
        printf("\t2. Create new partition in memory\n");
        scanf("%d", &mode);

        if (!(mode == 1 || mode == 2))
        {
            printf("Option error!\n\n");
        }
    }

    if (mode == 1)
    {
        char dump_name[50];
        printf("Please enter dump file name: ");
        scanf("%s", dump_name);
        file_system *fs = restore(dump_name);
    }
    else if (mode == 2)
    {
        long long partition_size;
        printf("Input size of a new partition (e.g. 102400): ");
        scanf("%lld", &partition_size);
        file_system *fs = initFileSystem(mode, partition_size);
    }

    return 0;
}