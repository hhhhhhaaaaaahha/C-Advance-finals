#include "status.h"
#include <stdio.h>

void print_status(file_system *fs, node *node){
    printf("\nparticion size: %lld\n", fs->partition_size);
    printf("total inodes: %d\n", NUM_TOTAL_INODES);
    printf("used inodes: %d\n", fs->num_used_inodes);
    printf("total blocks: %d\n", fs->num_total_blocks);
    printf("used blocks: %d\n", fs->num_used_blocks);
    printf("files' block: %d\n", count_blocks(fs));
    printf("block size: %d\n", BLOCK_SIZE);
    printf("free space: %lld\n",(fs->partition_size-BLOCK_SIZE*(fs->num_used_blocks)));
}

int count_blocks(file_system *fs) {
    int totalBlocks = 0;
    node *current = fs->root; 

    traverseFileSystem(current, &totalBlocks); 
    return totalBlocks;
}

void traverseFileSystem(node *current, int *totalBlocks) {
    if (current == NULL) return;

    if (current->file_info->node_type == TYPE_FILE) {
        *totalBlocks += current->file_info->num_used_blocks;
    }

    traverseFileSystem(current->left_most_child, totalBlocks);
    traverseFileSystem(current->sibling, totalBlocks);
}