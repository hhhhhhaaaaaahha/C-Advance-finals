#ifndef FS_H
#define FS_H

#include <stdlib.h>

#include "metadata.h"

#define BLOCK_SIZE 4096

typedef struct node node;

typedef struct file_system
{
    node *root;
    node *current_directory;

    long long partition_size;

    /* inode-related */
    int *inode_bitmap;
    int num_used_inodes;

    int *data_bitmap;
    int num_total_blocks;
    int num_used_blocks;

} file_system;

file_system *initFileSystem(int mode, long long partition_size);
int allocateInode(file_system *fs);
int allocateDataBlock(file_system *fs);
void reclaimInode(file_system *fs, int inum);
node *createFile(file_system *fs, node *parent, const char *name, file_type node_type);
void deleteFile(file_system *fs, node *target);
// TODO: implement this
void freeFileSystem(file_system *fs);

#endif