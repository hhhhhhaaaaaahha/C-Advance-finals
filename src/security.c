#include "security.h"
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>


int encode(char *str, char *key)
{
    int len = strlen(str);
    int key_len = strlen(key);
    for (int i = 0; i < len; i++)
    {
        str[i] = str[i] ^ key[i % key_len];
    }
    return 0;
}

int decode(char *str, char *key)
{
    int len = strlen(str);
    int key_len = strlen(key);
    for (int i = 0; i < len; i++)
    {
        str[i] = str[i] ^ key[i % key_len];
    }
    return 0;
}

int encodeWithPassword(char *str, char *buf, int len, char *password){
    int password_len = strlen(password);
    for(int i = 0; i < len; i++){
        buf[i] = str[i] ^ password[i % password_len];
    }
    return 0;
}

int decodeWithPassword(char *str, char *buf, int len, char *password){
    int password_len = strlen(password);
    for(int i = 0; i <= len; i++){
        buf[i] = str[i] ^ password[i % password_len];
    }
    return 0;
}

int encodeFile(char *filename, char *key)
{
    printf("filename is %s\n", filename);
    printf("key is %s\n", key);
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        return -1;
    }
    char c;
    int counter = 0;
    int key_len = strlen(key);
    fseek(fp, 0, SEEK_SET);
    while ((c = fgetc(fp)) != EOF)
    {
        fseek(fp, -1, SEEK_CUR);
        fputc(c ^ key[counter % key_len], fp);
        counter ++ ;
    }
    fclose(fp);
    return 0;
}

int decodeFile(char *filename, char *key)
{
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        return -1;
    }
    char c;
    int counter = 0;
    int key_len = strlen(key);
    while ((c = fgetc(fp)) != EOF)
    {
        fseek(fp, -1, SEEK_CUR);
        fputc(c ^ key[counter % key_len], fp);
        counter ++ ;
    }
    fclose(fp);
    return 0;
}