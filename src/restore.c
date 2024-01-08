#include "restore.h"
#include "fs.h"
#include "node.h"
#include "fs_utils.h"

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
            while(fgetc(dump_fp) != ':');
            fscanf(dump_fp, "%s", file_name);
            // strip the " at the beginning and end
            int len = strlen(file_name);
            for(int i = 0; i < len - 2; i++){
                file_name[i] = file_name[i + 1];
            }
            file_name[len - 3] = '\0';
            // construct file
            node * new_file = initNode(fs_r, root, file_name, TYPE_FILE);
            // TODO : after the file path in file system is implemented,
            //       we can use the path to construct file content
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

void remove_head_and_tail(char * str){
    int len = strlen(str);
    for(int i = 0; i < len - 2; i++){
        str[i] = str[i + 1];
    }
    str[len - 3] = '\0';
}

int construct_structure_simple(file_system * fs_r, FILE * dump_fp, node * root){
    // construct node structure according to dump file
    // return 0 if success, -1 if fail
    char c;
    while((c = fgetc(dump_fp)) != EOF){
        // first get name and type
        if(c == '{'){
            char node_name[NAME];
            char node_type[NAME];
            char node_parent[NAME];
            char node_external_path[NAME];
            while(fgetc(dump_fp) != ':');
            fscanf(dump_fp, "%s", node_name);
            while(fgetc(dump_fp) != ':');
            fscanf(dump_fp, "%s", node_type);
            while(fgetc(dump_fp) != ':');
            fscanf(dump_fp, "%s", node_parent);
            while(fgetc(dump_fp) != ':');
            fscanf(dump_fp, "%s", node_external_path);
            // strip the " at the beginning and end
            remove_head_and_tail(node_name);
            remove_head_and_tail(node_type);
            remove_head_and_tail(node_parent);
            remove_head_and_tail(node_external_path);
            // find parent node
            node * parent_node = find_dir(fs_r, node_parent);
            if(parent_node == NULL){
                printf("No such parent node : %s\n", node_parent);
                return -1;
            }

            // construct node
            node * new_node = initNode(fs_r, parent_node, node_name, strcmp(node_type, "dir") == 0 ? TYPE_DIR : TYPE_FILE);
            new_node->external_path = (char *)malloc(sizeof(char) * (strlen(node_external_path) + 1));
            strcpy(new_node->external_path, node_external_path);
        }
    }
    return 0;
}

file_system * restore_simple(const char * dump_file_name){
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
    construct_structure_simple(fs, dump_file, fs->root);
    fclose(dump_file);
    return fs;
}