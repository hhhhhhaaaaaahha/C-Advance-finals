#include "../include/fs.h"
#include "../include/metadata.h"
#include "../include/node.h"

#include <string.h>
#include <math.h>

node *initNode(file_system *fs, node *parent, const char *name, file_type node_type)
{
    node *new_node = (node *)malloc(sizeof(node));

    strcpy(new_node->name, name);
    new_node->inode = allocateInode(fs);

    /* Set related nodes */
    new_node->parent = parent;
    new_node->left_most_child = NULL;
    new_node->sibling = NULL;

    /* Check if parent already have children */
    if (parent != NULL) // Consider root doesn't have parent
    {
        node *it = parent->left_most_child;
        if (it != NULL)
        {
            while (it->sibling != NULL)
            {
                it = it->sibling;
            }
            it->sibling = new_node;
        }
        else
        {
            parent->left_most_child = new_node;
        }
    }

    /* Init metadata and link node with real file */
    initMetadata(fs, new_node, node_type);

    return new_node;
}