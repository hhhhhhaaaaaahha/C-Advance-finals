#include "../include/fs.h"
#include "../include/metadata.h"
#include "../include/node.h"

#include <stdio.h>
#include <string.h>

file_system *initFileSystem(int mode)
{
    file_system *fs = (file_system *)malloc(sizeof(file_system));

    /* init inode bitmap */
    fs->inode_bitmap = (int *)malloc(NUM_TOTAL_INODES * sizeof(int));
    fs->inode_bitmap[0] = 1; // assign inode number 0 to root directory
    for (int i = 1; i < NUM_TOTAL_INODES; i++)
    {
        fs->inode_bitmap[i] = 0;
    }

    fs->root = (node *)malloc(sizeof(node));
    strcpy(fs->root->name, "/");
    fs->root->child = NULL;
    fs->current_directory = fs->root;

    return fs;
}

void createFile(file_system *fs)
{
    int inum = allocateInode(fs);
}

void deleteFile(file_system *fs)
{
    // reclaimInode();
}

int allocateInode(file_system *fs)
{
    for (int i = 0; i < NUM_TOTAL_INODES; i++)
    {
        if (fs->inode_bitmap[i] == 0)
        {
            fs->inode_bitmap[i] = 1;
            return i;
        }
    }
}

void reclaimInode(file_system *fs, int inum)
{
    fs->inode_bitmap[inum] = 0;
}