#include "restore.h"
#include "fs.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int constructNodeStructure(file_system * fs_r, FILE * dump_fp, node * root){
    // construct node structure according to dump file
    // return 0 if success, -1 if fail
    char c;
    while((c = fgetc(dump_fp)) != EOF){
        if(c == ']'){
            break;
        }
        else if(c == '['){
            // construct a new node
            char node_name[NAME];
            fscanf(dump_fp, "%s", node_name);
            // construct node
            node * new_node = initNode(fs_r, root, node_name, TYPE_DIR);
            // construct node structure
            constructNodeStructure(fs_r, dump_fp, new_node);
        }
        else if(c == '{'){
            // construct a new file
            char file_name[NAME];
            fscanf(dump_fp, "%s", file_name);
            // construct file
            node * new_file = initNode(fs_r, root, file_name, TYPE_FILE);
            // construct file structure
            // char file_content[FILE_SIZE];
            // fscanf(dump_fp, "%s", file_content);
            // // write file content
            // fwrite(file_content, sizeof(char), strlen(file_content), new_file->fp);
        }
    }
    return 0;
}

file_system * restore(const char * dump_file_name){
    FILE * dump_file = fopen(dump_file_name, "r");
    if(dump_file == NULL){
        return NULL;
    }
    // construct file system according to dump file,
    // which content is json format
    file_system * fs;
    long long partition_size;
    // move file pointer to partition size
    while(fgetc(dump_file) != ':');
    fscanf(dump_file, "%lld", &partition_size);
    fs = initFileSystem(0, partition_size);
    // skip to child list to contruct file system
    char c;
    while((c = fgetc(dump_file)) != EOF){
        if(c == '['){
            break;
        }
    }
    // construct file system
    constructNodeStructure(fs, dump_file, fs->root);
    fclose(dump_file);
    return fs;
}