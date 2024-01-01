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
void cd(char *dir)
{
    Temp_Inode *inode = (Temp_Inode *)malloc(sizeof(Temp_Inode));
    // 若輸入cd ..
    if (strcmp(dir, "..") == 0)
    {
        prevDirectory();
    }
    // 若輸入cd /
    else if (strcmp(dir, "/") == 0)
    {
        backToRoot();
    }
    else if (dir)
    {
        //若不是輸入完整路徑，則將目前路徑加入欲找尋的path中
        if (open_file(dir, inode) == -1)
        {
            char complete_path[200];
            strcpy(complete_path, current);
            removeSubstring(complete_path, " $ ");
            strcat(complete_path, "/");
            strcat(complete_path, dir);
            //用完整路徑再次判斷
            if(open_file(complete_path, inode) == -1){
                printf("Not a exist directory!\n");
                return;
            }
            strcpy(current, complete_path);
        }else{
            strcpy(current, dir);
        }

        strcat(current, " $ ");
    }
}

// 回到根目錄
void backToRoot()
{
    strcpy(currentParent, "");
    strcpy(current, "/ $ ");
}

// 返回上一層目錄
void prevDirectory()
{
    char *lastSlash = strrchr(current, '/');

    if (lastSlash != NULL)
    {
        *lastSlash = '\0';
    }
    strcat(current, " $ ");
    // printf("Return to the previous directory: %s\n", current);
}

// linux輸入前會先印出自己在哪個folder底下
char *currentStatus()
{
    return current;
}