#ifndef INODE_H
#define INODE_H

#define NUM_TOTAL_INODES 500
#define FAKE_DIR_SIZE 2048

#include <stdio.h>

typedef struct file_system file_system;
typedef struct node node;

typedef enum file_type
{
    TYPE_FILE,
    TYPE_DIR,
} file_type;

typedef struct int_node
{
    int data;
    struct int_node *next;
} int_node;

typedef struct metadata
{
    int file_size;
    int num_used_blocks;
    file_type node_type;
    int_node *first_data_block;
} metadata;

void initMetadata(file_system *fs, node *new_node, file_type node_type);
int initMetadata_with_size(file_system *fs, node *new_node, file_type node_type, int file_size);


#endif