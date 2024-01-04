#pragma once

#include "fs.h"
#include "node.h"
#include "rmdir.h"

#include <string.h>

int rm(file_system *fs, const char *file_name);
