#ifndef FS_H
#define FS_H

#include <stdlib.h>

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

} file_system;

file_system *initFileSystem(int mode);
int allocateInode(file_system *fs);
void reclaimInode(file_system *fs, int inum);
void createFile(file_system *fs);
void deleteFile(file_system *fs);

#endif