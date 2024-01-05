#pragma once


#define MAX_PREFIX_LENGTH 1024

// enum for exit code
typedef enum {
    UI_EXIT_SUCCESS = 0,
    UI_EXIT_FAILURE = 1,
    UI_EXIT_PROCESS = 2,
} exit_code_t;

typedef struct file_system file_system;

exit_code_t fake_terminal(const char * command, file_system *fs);
void show_prefix(file_system *fs);
