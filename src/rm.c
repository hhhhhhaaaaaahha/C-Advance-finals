#include "../include/rm.h"
#include "fs_utils.h"

int rm(file_system *fs, const char *file_name){
    node *target = find_file(fs, file_name);
    if(target == NULL){
        printf("Not an exist file!\n");
        return -1;
    }
    deleteFile(fs, target);
    return 0;
}
