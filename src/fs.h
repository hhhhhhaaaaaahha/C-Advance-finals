#ifndef FS_H
#define FS_H

#include <stdlib.h>

#include "inode.h"

typedef struct file_system
{
    int *inode_bitmap;
} file_system;

file_system *initFileSystem();

#endif