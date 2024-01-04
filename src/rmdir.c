#include "rmdir.h"
#include "fs.h"
#include "node.h"
#include "util.h"
#include <string.h>

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

