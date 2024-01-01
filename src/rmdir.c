#include "rmdir.h"
#include "fs.h"
#include "node.h"
#include <string.h>

// find dir in current directory
node *find_dir(file_system *fs, const char *folder_name)
{
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

// delete whole folder
int rm_dir_inline(file_system *fs, node *target)
{
    // delete whole folder
    node *it = target->left_most_child;
    while (it != NULL)
    {
        if (it->file_info->node_type == TYPE_DIR)
        {
            rm_dir_inline(fs, it);
        }
        else
        {
            deleteFile(fs, it);
        }
        it = it->sibling;
    }
    deleteFile(fs, target);
    return 0;
}


// remove directory from current directory, recursively
int rm_dir(file_system *fs, const char *folder_name)
{
    node *target = find_dir(fs, folder_name);
    if (target == NULL)
    {
        printf("No such directory\n");
        return -1;
    }

    // delete whole folder
    node *it = target->left_most_child;
    while (it != NULL)
    {
        if (it->file_info->node_type == TYPE_DIR)
        {
            rm_dir_inline(fs, it);
        }
        else
        {
            deleteFile(fs, it);
        }
        it = it->sibling;
    }

    // delete target node
    deleteFile(fs, target);
    return 0;
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
    return find_file_inline(fs, it, file_name);
}