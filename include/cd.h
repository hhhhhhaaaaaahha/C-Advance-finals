#pragma once 

#include "node.h"
#include "put.h"
#include "rmdir.h"
#include "fs.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int cd(file_system * fs,char *dir);
void backToRoot(file_system * fs);
int prevDirectory(file_system * fs);
char *currentStatus();
