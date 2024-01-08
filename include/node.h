#ifndef NODE_H
#define NODE_H

#include "metadata.h"

#include <stdio.h>

#define NAME 50

typedef struct metadata metadata;
typedef struct file_system file_system;
typedef enum file_type file_type;

typedef struct node
{
    char name[50];
    // what is this? inode number?
    int inode;

    node *parent;
    node *left_most_child;
    node *sibling;

    // FILE *fp; // remember to close this
    char external_path[100];

    metadata *file_info;
} node;

node *initNode(file_system *fs, node *parent, const char *name, file_type node_type);


#endif