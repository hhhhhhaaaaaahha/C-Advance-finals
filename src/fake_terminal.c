#include "fake_terminal.h"
#include "fs.h"
#include "node.h"
#include "cat.h"
#include "put.h"
#include "cd.h"
#include "mkdir.h"
#include "get.h"
#include "ls.h"
#include "rmdir.h"
#include "rm.h"
#include "status.h"
#include "help.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void show_prefix(file_system *fs)
{
    // add cwd to prefix
    char cwd[MAX_PREFIX_LENGTH] = {0};
    
    strcpy(cwd, "");
    node *it = fs->current_directory;

    if (it == fs->root)
    {
        strcpy(cwd, "/");
        printf("%s $ ", cwd);
        return;
    }

    while (it != fs->root)
    {
        // add to front of cwd
        char *temp = (char *)malloc(sizeof(char) * (MAX_PREFIX_LENGTH + 1));
        strcpy(temp, "/");
        strcat(temp, it->name);
        strcat(temp, cwd);
        strcpy(cwd, temp);
        free(temp);
        it = it->parent;
    }
    printf("%s $ ", cwd);
}

exit_code_t fake_terminal(const char *command, file_system *fs)
{
    // split command
    char *command_copy = (char *)malloc(sizeof(char) * (strlen(command) + 1));

    strcpy(command_copy, command);
    command_copy[strlen(command_copy)-1] = '\0';
    char *command_split = strtok(command_copy, " ");
    if(command_split == NULL){
        return UI_EXIT_SUCCESS;
    }
    if (strcmp(command_split, "ls") == 0)
    {
        // ls
        char * temp_buff = lsPrint(fs->current_directory);
        if(temp_buff != NULL)printf("%s", temp_buff);
        return UI_EXIT_SUCCESS;
    }
    else if (strcmp(command_split, "cd") == 0)
    {
        // cd
        command_split = strtok(NULL, " ");
        if (command_split == NULL)
        {
            printf("Usage: cd <directory name>\n");
            return UI_EXIT_FAILURE;
        }
        if (cd(fs, command_split) == -1)
        {
            // printf("cd: Directory not found.\n");
            return UI_EXIT_FAILURE;
        }
        return UI_EXIT_SUCCESS;
    }
    else if (strcmp(command_split, "mkdir") == 0)
    {
        // mkdir
        command_split = strtok(NULL, " ");
        if (command_split == NULL)
        {
            printf("Usage: mkdir <directory name>\n");
            return UI_EXIT_FAILURE;
        }

        if (mk_dir(fs, command_split) == -1)
        {
            // printf("mkdir: Directory already exists.\n");
            return UI_EXIT_FAILURE;
        }
        printf("mkdir: Directory created successfully.\n");
        return UI_EXIT_SUCCESS;
    }
    else if (strcmp(command_split, "rmdir") == 0)
    {
        // rmdir
        command_split = strtok(NULL, " ");
        if (command_split == NULL)
        {
            printf("Usage: rmdir <directory name>\n");
            return UI_EXIT_FAILURE;
        }
        if (rm_dir(fs, command_split) == -1)
        {
            // printf("rmdir: Directory not found.\n");
            return UI_EXIT_FAILURE;
        }
        printf("rmdir: Directory removed successfully.\n");
        
        return UI_EXIT_SUCCESS;
    }
    else if (strcmp(command_split, "rm") == 0)
    {
        // rm
        command_split = strtok(NULL, " ");
        if (command_split == NULL)
        {
            printf("Usage: rm <file name>\n");
            return UI_EXIT_FAILURE;
        }

        if (rm(fs, command_split) == -1)
        {
            // printf("rm: File not found.\n");
            return UI_EXIT_FAILURE;
        }
        printf("rm: File removed successfully.\n");
        return UI_EXIT_SUCCESS;
    }
    else if (strcmp(command_split, "cat") == 0)
    {
        // cat
        command_split = strtok(NULL, " ");
        if (command_split == NULL)
        {
            printf("Usage: cat <filename>\n");
            return UI_EXIT_FAILURE;
        }
        char * file_cp = (char *)malloc(sizeof(char) * (strlen(command_split) + 1));
        strcpy(file_cp, command_split);
        find_and_print(fs, file_cp);
        return UI_EXIT_SUCCESS;
    }
    else if (strcmp(command_split, "put") == 0)
    {
        // put
        command_split = strtok(NULL, " ");
        if (command_split == NULL)
        {
            printf("Usage: put <external file path>\n");
            return UI_EXIT_FAILURE;
        }
        if (put_file(fs, command_split) == NULL)
        {
            printf("put: File not found.\n");
            return UI_EXIT_FAILURE;
        }
        printf("put: File put successfully.\n");
        return UI_EXIT_SUCCESS;
    }
    else if (strcmp(command_split, "help") == 0)
    {
        // help
        help();
        return UI_EXIT_SUCCESS;
    }
    else if (strcmp(command_split, "exit") == 0)
    {
        // exit
        printf("Goodbye!\n");
        return UI_EXIT_PROCESS;
    }
    else if (strcmp(command_split, "get") == 0)
    {
        // get
        command_split = strtok(NULL, " ");
        if (command_split == NULL)
        {
            printf("Usage: get <file name>\n");
            return UI_EXIT_FAILURE;
        }
        if (get_file(fs, command_split) == -1)
        {
            return UI_EXIT_FAILURE;
        }
        printf("get: File get successfully.\n");
        return UI_EXIT_SUCCESS;
    }
    else if(strcmp(command_split, "status")==0){
        // status
        print_status(fs, fs->root);
        return UI_EXIT_SUCCESS;
    }
    else
    {
        printf("Command not found!\n");
        return UI_EXIT_SUCCESS;
    }
}