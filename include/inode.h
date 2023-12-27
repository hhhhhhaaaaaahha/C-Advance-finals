#ifndef INODE_H
#define INODE_H

#define NUM_TOTAL_INODES 500

typedef enum file_type
{
    // suggest using a different name for this enum
    // since it may conflict with some varible names.
    TYPE_FILE, // uppercase
    TYPE_DIR,  // uppercase
} file_type;


typedef struct metadata // should filetype be in here?
{
    int file_size;
    int *blocks;
} metadata;

void helloWorld();

#endif