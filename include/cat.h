#ifndef CAT_H
#define CAT_H

#include "node.h"
#include "fs.h"
#include <string.h>

void find_and_print(file_system *fs, const char *filename);
node *findFile(node *current_directory, const char *filename) ;
#endif
