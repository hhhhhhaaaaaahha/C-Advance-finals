#pragma once

typedef struct file_system file_system;

// dump the file system in a file called file_name in json format
int dump(file_system *fs, const char *file_name);
int dump_simple(file_system *fs, const char *file_name);
