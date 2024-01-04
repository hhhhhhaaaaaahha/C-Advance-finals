#include "../include/fs.h"
#include "../include/metadata.h"
#include "../include/node.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

file_system *initFileSystem(int mode, long long partition_size)
{
    file_system *fs = (file_system *)malloc(sizeof(file_system));

    fs->partition_size = partition_size;

    /* init inode bitmap */
    fs->inode_bitmap = (int *)malloc(NUM_TOTAL_INODES * sizeof(int));
    fs->num_used_inodes = 0;
    for (int i = 0; i < NUM_TOTAL_INODES; i++)
    {
        fs->inode_bitmap[i] = 0;
    }

    /* init data bitmap */
    fs->num_total_blocks = (partition_size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    fs->data_bitmap = (int *)malloc(fs->num_total_blocks * sizeof(int));
    fs->num_used_blocks = 0;
    for (int i = 0; i < fs->num_total_blocks; i++)
    {
        fs->data_bitmap[i] = 0;
    }

    /* Create root node */
    fs->root = initNode(fs, NULL, "/", TYPE_DIR);
    fs->current_directory = fs->root;

    return fs;
}

node *createFile(file_system *fs, node *parent, const char *name, file_type node_type)
{
    return initNode(fs, parent, name, node_type);
}

void deleteFile(file_system *fs, node *target)
{
    if (target == fs->root)
    {
        printf("Cannot delete root!!!\n");
        return;
    }
    reclaimInode(fs, target->inode);

    node *it = target->parent->left_most_child;
    if (it == target)
    {
        it->parent->left_most_child = it->sibling;
    }
    else
    {
        while (it->sibling != target)
        {
            it = it->sibling;
        }
        it->sibling = target->sibling;
    }

    free(target->file_info);
    free(target);
}

int allocateInode(file_system *fs)
{
    for (int i = 0; i < NUM_TOTAL_INODES; i++)
    {
        if (fs->inode_bitmap[i] == 0)
        {
            fs->inode_bitmap[i] = 1;
            fs->num_used_inodes++;
            return i;
        }
    }
    return -1;
}

void reclaimInode(file_system *fs, int inum)
{
    fs->inode_bitmap[inum] = 0;
}

int allocateDataBlock(file_system *fs)
{
    for (int i = 0; i < fs->num_total_blocks; i++)
    {
        if (fs->data_bitmap[i] == 0)
        {
            fs->data_bitmap[i] = 1;
            fs->num_used_blocks++;
            return i;
        }
    }
    return -1;
}