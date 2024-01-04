#include "../include/mkdir.h"

int mk_dir(file_system *fs, const char *folder_name){
    node *new_folder;
    if(find_dir(fs, folder_name) != NULL){
        printf("Folder Exist!\n");
        return -1;
    }
    new_folder = createFile(fs, fs->current_directory, folder_name, TYPE_DIR);
    return 0;
}