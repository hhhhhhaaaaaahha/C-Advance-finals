#include "fs_utils.h"
#include "fs.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// find dir in current directory
node *find_dir(file_system *fs, const char *folder_name)
{
    if(strcmp(folder_name, "/") == 0){
        return fs->root;
    }
    node *it = fs->current_directory->left_most_child;
    while (it != NULL)
    {
        if (strcmp(it->name, folder_name) == 0 && it->file_info->node_type == TYPE_DIR)
        {
            return it;
        }
        it = it->sibling;
    }
    return NULL;
}


node *find_file_inline(file_system *fs, node *target, const char *file_name)
{
    node * ret = NULL;
    node *it = target->left_most_child;
    while (it != NULL)
    {
        if (it->file_info->node_type == TYPE_DIR)
        {
            ret = find_file_inline(fs, it, file_name);
            if (ret != NULL)
            {
                return ret;
            }
        }
        else if (strcmp(it->name, file_name) == 0 && it->file_info->node_type == TYPE_FILE)
        {
            return it;
        }
        it = it->sibling;
    }
    printf("No such file\n");
    return NULL;
}

// utility for test to find the file under current directory
node *find_file(file_system *fs, const char *file_name)
{
    node *it = fs->current_directory->left_most_child;
    node *ret = NULL;
    while (it != NULL)
    {
        if (it->file_info->node_type == TYPE_DIR)
        {
            ret = find_file_inline(fs, it, file_name);
            if (ret != NULL)
            {
                return ret;
            }
        }
        else if (strcmp(it->name, file_name) == 0 && it->file_info->node_type == TYPE_FILE)
        {
            return it;
        }
        it = it->sibling;
    }
    return NULL;
}