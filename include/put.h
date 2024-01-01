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

int open_file_for_test(const char * path, Temp_Inode * inode);
int open_file(const char * path, node * inode);
node * put_file(file_system *fs, const char *path);
node * put_folder(file_system *fs, const char *path); // please ignore this function
int read_file_buffer(Temp_Inode * inode, FILE * file, int size);

int check_node_size(const char * path);