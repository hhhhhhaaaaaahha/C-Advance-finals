#include "../include/put.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int open_file(const char * path, Temp_Inode * inode){
    // initialize the inode
    inode->metadata = (metadata_temp*)malloc(sizeof(metadata_temp));
    // open the file
    FILE * file = fopen(path, "r");
    if(file == NULL){
        return -1;
    }
    fseek(file, 0, SEEK_END);
    inode->metadata->size = ftell(file);
    // record the open file is a file or directory
    struct stat statbuf = {0};
    stat(path, &statbuf);
    if(S_ISDIR(statbuf.st_mode)){
        inode->metadata->type = TYPE_DIR;
    }else if(S_ISREG(statbuf.st_mode)){
        inode->metadata->type = TYPE_FILE;
    }else{
        return -1; // not a file or directory
    }
    // copy the name of the file to the inode
    inode->metadata->name = (char*)malloc(sizeof(char) * strlen(path));
    strncpy(inode->metadata->name, path, strlen(path));
    // record the size of the file (byte)
    inode->metadata->size = ftell(file);
    // read the file to the buffer
    read_file_buffer(inode, file, inode->metadata->size);
    // close the file
    fclose(file);
    return 0;
}

int read_file_buffer(Temp_Inode * inode, FILE * file, int size){
    // read the file to the buffer
    inode->content = (char*)malloc(sizeof(char) * size);
    fseek(file, 0, SEEK_SET);
    fread(inode->content, sizeof(char), size, file);
    return 0;
}