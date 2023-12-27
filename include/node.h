#ifndef NODE_H
#define NODE_H

#define NAME 50

typedef struct node
{
    char name[50];
    int inode;
    node *child;
    node *parent;

} node;

#endif