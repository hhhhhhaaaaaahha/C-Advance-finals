#include <stdio.h>

#include "../include/metadata.h"
#include "../include/node.h"
#include "../include/fs.h"

void initMetadata(file_system *fs, node *new_node, file_type node_type)
{
    metadata *info = (metadata *)malloc(sizeof(metadata));
    info->node_type = node_type;
    if (node_type == TYPE_DIR)
    {
        new_node->fp = NULL;
        info->file_size = FAKE_DIR_SIZE;
    }
    else if (node_type == TYPE_FILE)
    {
        new_node->fp = NULL;
        info->file_size = FAKE_DIR_SIZE;
    }
    
    info->num_used_blocks = (info->file_size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    /* Allocate data blocks to node */
    info->first_data_block = (int_node *)malloc(sizeof(int_node));
    info->first_data_block->data = allocateDataBlock(fs);
    info->first_data_block->next = NULL;
    int_node *it = info->first_data_block;
    for (int i = 0; i < info->num_used_blocks - 1; i++)
    {
        int_node *new_block = (int_node *)malloc(sizeof(int_node));
        new_block->data = allocateDataBlock(fs);
        new_block->next = NULL;
        it->next = new_block;
        it = new_block;
    }
    new_node->file_info = info;
}

