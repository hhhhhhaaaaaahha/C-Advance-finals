#include "../include/cat.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief A function to mimic a linux command cd
 * 
 * @param fs 
 * @param filename 
 */
void find_and_print(file_system *fs, const char *filename) {
    // find out which node does the file locate at
    node *file = findFile(fs->current_directory, filename); 
    if (file == NULL || file->file_info->node_type != TYPE_FILE) {
        printf("File not found or is not a regular file.\n");
        return;
    }

    FILE *fp = fopen(file->external_path, "r"); // point to the real file
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }


    size_t file_size = file->file_info->file_size;
    char *file_content = (char *)malloc(file_size * sizeof(char));
    if (file_content == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // read file's content
    fread(file_content, sizeof(char), file_size, fp);
    // print content to terminal
    fwrite(file_content, sizeof(char), file_size, stdout);

    // release and reset
    free(file_content);
    fseek(fp, 0, SEEK_SET);
    fclose(fp);
}


/**
 * @brief Find a node in a folder node, recursively
 * 
 * @param current_directory 
 * @param filename 
 * @return node* 
 */
node *findFile(node *current_directory, const char *filename) {
    node *current = current_directory->left_most_child;
    while (current != NULL) {
        if (strcmp(current->name, filename) == 0 && current->file_info->node_type == TYPE_FILE) {
            return current;
        }
        current = current->sibling;
    }
    return NULL; 
}
