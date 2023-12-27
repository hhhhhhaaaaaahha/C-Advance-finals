#pragma once
#include "inode.h"
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
int read_file_buffer(Temp_Inode * inode, FILE * file, int size);