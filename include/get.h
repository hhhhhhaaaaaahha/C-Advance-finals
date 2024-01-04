#pragma once
#include <sys/stat.h>
#define DUMP_FOLDER "dump"

typedef struct file_system file_system;

int create_dump_folder();
int check_dump_folder();
int get_file(file_system *fs, const char *file_name);
