#ifndef INODE_H
#define INODE_H

#define NUM_TOTAL_INODES 500

typedef enum file_type
{
    TYPE_FILE,
    TYPE_DIR,
} file_type;

typedef struct metadata // should filetype be in here?
{
    int file_size;
    int *blocks;
    file_type node_type;
} metadata;

#endif