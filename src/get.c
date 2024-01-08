#include "get.h"
#include "fs.h"
#include "node.h"
#include "rmdir.h"
#include "fs_utils.h"

#include <stdio.h>
#include <stdlib.h>

int check_dump_folder()
{
    struct stat st = {0};
    if (stat(DUMP_FOLDER, &st) == -1)
    {
        return 1;
    }
    return 0;
}

int create_dump_folder()
{
    if (check_dump_folder() == 0)
        return 0; // folder exists
    struct stat st = {0};
    if (stat(DUMP_FOLDER, &st) == -1)
    {
        mkdir(DUMP_FOLDER, 0700);
    }
    return 0;
}

char * get_file_content(file_system *fs, node *file_node)
{
    FILE *file = fopen(file_node->external_path, "r");
    size_t file_size = file_node->file_info->file_size;
    char *file_content = (char *)malloc(file_size * sizeof(char));
    int i;
    for (i = 0; i < file_size; i++)
    {
        file_content[i] = fgetc(file);
    }
    fseek(file, 0, SEEK_SET);
    return file_content;
}

int get_file(file_system *fs, const char *file_name)
{
    // check if file exists
    node * found_node = find_file(fs, file_name);
    if (found_node == NULL)
    {
        printf("File not found\n");
        return -1;
    }

    // create dump folder if not exists
    if (create_dump_folder() == 1)
    {
        printf("Error creating dump folder\n");
        return -1;
    }

    // create file in dump folder
    char dump_file_path[100];
    sprintf(dump_file_path, "%s/%s", DUMP_FOLDER, file_name);
    FILE *dump_file = fopen(dump_file_path, "w");
    if (dump_file == NULL)
    {
        printf("Error creating dump file\n");
        return -1;
    }
    // get file content
    char *file_content = get_file_content(fs, found_node);    

    // write file content to dump file
    int i;
    for (i = 0; i < found_node->file_info->file_size; i++)
    {
        fputc(file_content[i], dump_file);
    }
    fclose(dump_file);
    return 0;
}