#pragma once

int encode(char *str, char *buf, int len);
int decode(char *str, char *buf, int len);
int encodeWithPassword(char *str, char *buf, int len, char *password);
int decodeWithPassword(char *str, char *buf, int len, char *password);