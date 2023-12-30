#pragma once
#include "metadata.h"
#include "node.h"
#include "fs.h"
#include <stdio.h>

typedef struct {
    char * name;
    int type;
    int size;
    // int block_count;
    // int block_ids[10];
} metadata_temp;

typedef struct {
    metadata_temp * metadata;
    char * content;
} Temp_Inode;

int open_file(const char * path, Temp_Inode * inode);
int open_file(const char * path, node * inode);
node * put_file(file_system *fs, const char *path);
int read_file_buffer(Temp_Inode * inode, FILE * file, int size);