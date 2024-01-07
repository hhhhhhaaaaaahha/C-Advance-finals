#include "include/metadata.h"
#include "include/fs.h"
#include "restore.h"
#include "dump.h"
#include "fake_terminal.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CMD_SIZE 1024

int main(void)
{
    int mode = 0;
    file_system * fs;
    char * command = (char*)malloc(CMD_SIZE);
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
        fs = restore_simple(dump_name);
    }
    else if (mode == 2)
    {
        long long partition_size;
        printf("Input size of a new partition (e.g. 102400): ");
        scanf("%lld", &partition_size);
        fs = initFileSystem(mode, partition_size);
    }
    getc(stdin);
    // terminal part
    while(1){
        memset(command, 0, CMD_SIZE);
        show_prefix(fs);
        fgets(command, CMD_SIZE, stdin);
        int ret = fake_terminal(command, fs);
        if(ret == UI_EXIT_PROCESS) break;
    }
    const char * dump_file_name = "my_fs";
    int ret = dump_simple(fs, dump_file_name);
    if(ret == 0) printf("Dump file %s.dump successfully create!\n", dump_file_name);
    free(command);
    return 0;
}