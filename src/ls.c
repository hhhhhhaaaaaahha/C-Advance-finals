#include "../include/ls.h"


// node * ls(char * name){}
char allFileFolderList[500];

char* lsPrint(node *dir){
    if(dir && dir->left_most_child){
        node *it = dir->left_most_child;
        while (it)
        {
            //將遍歷到的file, folder名稱存入allFileFolderList
            // printf("%s\n",it->name);
            strcat(allFileFolderList, it->name);
            strcat(allFileFolderList, "\n");
            //移動到同一個資料夾的下一個檔案
            it = it->sibling;
        }
        return allFileFolderList;
    }
    return NULL;
}