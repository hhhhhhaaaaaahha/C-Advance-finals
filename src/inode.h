#ifndef INODE_H
#define INODE_H

#define NUM_TOTAL_INODES 500

typedef enum file_type
{
    file,
    directory,
} file_type;

typedef struct metadata
{
    int file_size;
    int *blocks;
} metadata;

void helloWorld();

#endif