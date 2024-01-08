#pragma once

int encode(char *str, char * key);
int decode(char *str, char * key);
int encodeWithPassword(char *str, char *buf, int len, char *password);
int decodeWithPassword(char *str, char *buf, int len, char *password);
int encodeFile(char *filename, char *key);
int decodeFile(char *filename, char *key);
