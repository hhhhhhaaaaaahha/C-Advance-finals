#include "fs.h"

struct file_system *initFileSystem()
{
    file_system *fs = (file_system *)malloc(sizeof(file_system));
    fs->inode_bitmap = (int *)malloc(NUM_TOTAL_INODES * sizeof(int));
}