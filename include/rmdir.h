#pragma once

typedef struct file_system file_system;
typedef struct node node;

int rm_dir(file_system *fs, const char * folder_name);
node * find_dir(file_system *fs, const char *folder_name);
node * find_file(file_system *fs, const char *file_name);