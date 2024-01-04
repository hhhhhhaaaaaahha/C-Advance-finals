#include "../include/cd.h"

char current[200] = "/ $ ";
char *currentParent;

//去除char *的substring (不是給client用的)
void removeSubstring(char *str, const char *sub) {
    size_t len = strlen(sub);
    char *p;

    // 循環查找子字符串
    while ((p = strstr(str, sub)) != NULL) {
        // 将子字符串之后的部分向前移动
        memmove(p, p + len, strlen(p + len) + 1);
    }
}

//cd主要判斷程式
int cd(file_system * fs,char *dir)
{
    // Temp_Inode *inode = (Temp_Inode *)malloc(sizeof(Temp_Inode)); // remember to compile before you commit
    node * inode = (node *)malloc(sizeof(node));
    // 若輸入cd ..
    if (strcmp(dir, "..") == 0)
    {
        prevDirectory(fs);
    }
    // 若輸入cd /
    else if (strcmp(dir, "/") == 0)
    {
        backToRoot(fs);
    }
    else {        
        node *it = find_dir(fs, dir);
        if(it == NULL){
            printf("Not a exist directory!\n");
            return -1;
        }else{
            fs->current_directory = it;
            removeSubstring(current, " $ ");
            if(it->parent != NULL && strcmp(it->parent->name, "/") == 0)
            {
                if(strcmp(current, "/") != 0){
                    memset(current, 0, sizeof(current));
                    strcat(current, "/");
                }
            }else{
                strcat(current, "/");
            }
            strcat(current, dir);
            strcat(current, " $ ");
            return 0;
        }
    }
}

// 回到根目錄
void backToRoot(file_system * fs)
{
    memset(current, 0, sizeof(current));
    strcpy(current, "/ $ ");
    fs->current_directory = fs->root;
}

// 返回上一層目錄
int prevDirectory(file_system * fs)
{
    char *lastSlash = strrchr(current, '/');

    if (lastSlash != NULL)
    {
        *lastSlash = '\0';
    }
    strcat(current, " $ ");
    node *dirParent = fs->current_directory->parent;
    if(dirParent == NULL){
        printf("Already at root!\n");
        return -1;
    }else{
        fs->current_directory = dirParent;
        return 0;
    }
}

// linux輸入前會先印出自己在哪個folder底下
char *currentStatus()
{
    return current;
}