#include "get.h"

int check_dump_folder(){
    struct stat st = {0};
    if (stat(DUMP_FOLDER, &st) == -1) {
        return 1;
    }
    return 0;
}

int create_dump_folder(){
    if(check_dump_folder()==0) return 0; // folder exists
    struct stat st = {0};
    if (stat(DUMP_FOLDER, &st) == -1) {
        mkdir(DUMP_FOLDER, 0700);
    }
    return 0;
}