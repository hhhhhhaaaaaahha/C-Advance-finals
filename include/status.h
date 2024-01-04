#ifndef STATUS_H
#define STATUS_H

#include "fs.h"
#include "node.h"

void print_status(file_system *fs, node *node);
int count_blocks(file_system *fs);
void traverseFileSystem(node *current, int *totalBlocks);

#endif