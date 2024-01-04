#pragma once

typedef struct file_system file_system;

file_system * restore(const char * dump_file_name);
file_system * restore_simple(const char * dump_file_name);