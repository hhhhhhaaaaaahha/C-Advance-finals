#pragma once

typedef struct file_system file_system;
typedef struct node node;

// find dir in current directory
node *find_dir(file_system *fs, const char *folder_name);

// utility for test to find the file under current directory
node *find_file(file_system *fs, const char *file_name);