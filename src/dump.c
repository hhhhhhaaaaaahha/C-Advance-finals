#include "dump.h"
#include "fs.h"
#include "node.h"
#include "status.h"
#include <string.h>
#include <unistd.h>

long long free_space(file_system *fs)
{
    return fs->partition_size - fs->num_used_blocks * BLOCK_SIZE;
}

int record_children_in_dump(file_system *fs, node *parent, FILE *dump_file, char *prefix)
{
    // record children
    node *it = parent->left_most_child;
    while (it != NULL)
    {
        // record child node
        fprintf(dump_file, "%s{\n", prefix);
        // record child node name
        fprintf(dump_file, "%s\t\"name\": \"%s\",\n", prefix, it->name);
        // record child node type
        fprintf(dump_file, "%s\t\"type\": \"%s\",\n", prefix, it->file_info->node_type == TYPE_DIR ? "dir" : "file");
        // record child node size
        fprintf(dump_file, "%s\t\"size\": %d,\n", prefix, it->file_info->file_size);
        // record child node block
        fprintf(dump_file, "%s\t\"blocks\": %d,\n", prefix, it->file_info->num_used_blocks);
        // record child node parent
        fprintf(dump_file, "%s\t\"parent\": \"%s\",\n", prefix, parent->name);
        // earily return if the child node has no children
        if (it->left_most_child == NULL)
        {
            fprintf(dump_file, "%s\t\"children\": []\n", prefix);
            fprintf(dump_file, "%s},\n", prefix);
            it = it->sibling;
            continue;
        }
        // record child node children
        fprintf(dump_file, "%s\t\"children\": [\n", prefix);
        // record child node children
        char *new_prefix = (char *)malloc(sizeof(char) * (strlen(prefix) + 2));
        strcpy(new_prefix, prefix);
        strcat(new_prefix, "\t");
        int ret = record_children_in_dump(fs, it, dump_file, new_prefix);
        free(new_prefix);
        // record child node children
        fprintf(dump_file, "%s\t]\n", prefix);
        // record child node
        fprintf(dump_file, "%s},\n", prefix);
        it = it->sibling;
    }
    return 0;
}

int record_root_in_dump(file_system *fs, node *root, FILE *dump_file)
{
    // record root node
    fprintf(dump_file, "\t\"root\": {\n");
    // record root node name
    fprintf(dump_file, "\t\t\"name\": \"%s\",\n", root->name);
    // record root node type
    fprintf(dump_file, "\t\t\"type\": \"%s\",\n", root->file_info->node_type == TYPE_DIR ? "dir" : "file");
    // record root node size
    fprintf(dump_file, "\t\t\"size\": %d,\n", root->file_info->file_size);
    // record root node block
    fprintf(dump_file, "\t\t\"blocks\": %d,\n", root->file_info->num_used_blocks);
    // record root node parent
    fprintf(dump_file, "\t\t\"parent\": null,\n");
    // earily return if the root node has no children
    if (root->left_most_child == NULL)
    {
        fprintf(dump_file, "\t\t\"children\": []\n");
        fprintf(dump_file, "\t}\n");
        return 0;
    }
    // record root node children
    fprintf(dump_file, "\t\t\"children\": [\n");
    char *prefix = "\t\t\t";
    int ret = record_children_in_dump(fs, root, dump_file, prefix);
    // record root node children
    fprintf(dump_file, "\t\t]\n");
    // record root node
    fprintf(dump_file, "\t}\n");
    return ret;
}

int dump(file_system *fs, const char *file_name)
{
    // create create dump file
    char *dump_file_name = (char *)malloc(sizeof(char) * (strlen(file_name) + 5));
    strcpy(dump_file_name, file_name);
    strcat(dump_file_name, ".dump");
    // check if the file exists
    if (access(dump_file_name, F_OK) != -1)
    {
        // file exists
        printf("Error: file %s already exists\n", dump_file_name);
        free(dump_file_name);
        return -1;
    }
    FILE *dump_file = fopen(dump_file_name, "w");
    free(dump_file_name);
    // write file system info in json format
    fprintf(dump_file, "{\n");
    // partition size
    fprintf(dump_file, "\t\"partition_size\": %d,\n", fs->partition_size);
    // total number of inode
    fprintf(dump_file, "\t\"total_inodes\": %d,\n", NUM_TOTAL_INODES);
    // used inode
    fprintf(dump_file, "\t\"used_inodes\": %d,\n", fs->num_used_inodes);
    // total number of data block
    fprintf(dump_file, "\t\"total_blocks\": %d,\n", fs->num_total_blocks);
    // used data block
    fprintf(dump_file, "\t\"used_blocks\": %d,\n", fs->num_used_blocks);
    // files' block
    fprintf(dump_file, "\t\"files_block\": %d,\n", count_blocks(fs));
    // block size
    fprintf(dump_file, "\t\"block_size\": %d,\n", BLOCK_SIZE);
    // free space
    fprintf(dump_file, "\t\"free_space\": %lld,\n", free_space(fs));

    // record the root structure
    int ret = record_root_in_dump(fs, fs->root, dump_file);
    // end the bracket
    fprintf(dump_file, "}\n");
    fclose(dump_file);
    return ret;
}

int record_children_in_dump_simple(file_system *fs, node *parent, FILE *dump_file, char *prefix)
{
    // record children
    node *it = parent->left_most_child;
    while (it != NULL)
    {
        // record child node
        fprintf(dump_file, "%s{\n", prefix);
        // record child node name
        fprintf(dump_file, "%s\t\"name\": \"%s\",\n", prefix, it->name);
        // record child node type
        fprintf(dump_file, "%s\t\"type\": \"%s\",\n", prefix, it->file_info->node_type == TYPE_DIR ? "dir" : "file");
        // record child node parent
        fprintf(dump_file, "%s\t\"parent\": \"%s\",\n", prefix, parent->name);
        // earily return if the child node has no children
        if (it->left_most_child == NULL)
        {
            fprintf(dump_file, "%s\t\"children\": []\n", prefix);
            fprintf(dump_file, "%s},\n", prefix);
            it = it->sibling;
            continue;
        }
        // record child node children
        fprintf(dump_file, "%s\t\"children\": [\n", prefix);
        // record child node children
        char *new_prefix = (char *)malloc(sizeof(char) * (strlen(prefix) + 2));
        strcpy(new_prefix, prefix);
        strcat(new_prefix, "\t\t");
        int ret = record_children_in_dump_simple(fs, it, dump_file, new_prefix);
        free(new_prefix);
        // record child node children
        fprintf(dump_file, "%s\t]\n", prefix);
        // record child node
        fprintf(dump_file, "%s},\n", prefix);
        it = it->sibling;
    }
    return 0;
}

int record_root_in_dump_simple(file_system *fs, node *root, FILE *dump_file)
{
    // record root node
    fprintf(dump_file, "\t\"root\": {\n");
    // record root node name
    fprintf(dump_file, "\t\t\"name\": \"%s\",\n", root->name);
    // record root node type
    fprintf(dump_file, "\t\t\"type\": \"%s\",\n", root->file_info->node_type == TYPE_DIR ? "dir" : "file");
    // record root node parent
    fprintf(dump_file, "\t\t\"parent\": null,\n");
    // earily return if the root node has no children
    if (root->left_most_child == NULL)
    {
        fprintf(dump_file, "\t\t\"children\": []\n");
        fprintf(dump_file, "\t}\n");
        return 0;
    }
    // record root node children
    fprintf(dump_file, "\t\t\"children\": [\n");
    char *prefix = "\t\t\t";
    int ret = record_children_in_dump_simple(fs, root, dump_file, prefix);
    // record root node children
    fprintf(dump_file, "\t\t]\n");
    // record root node
    fprintf(dump_file, "\t}\n");
    return ret;
}

int dump_simple(file_system *fs, const char *file_name)
{
    // create create dump file
    char *dump_file_name = (char *)malloc(sizeof(char) * (strlen(file_name) + 5));
    strcpy(dump_file_name, file_name);
    strcat(dump_file_name, ".dump");
    // check if the file exists
    if (access(dump_file_name, F_OK) != -1)
    {
        // file exists
        printf("Error: file %s already exists\n", dump_file_name);
        free(dump_file_name);
        return -1;
    }
    FILE *dump_file = fopen(dump_file_name, "w");
    free(dump_file_name);
    // write file system info in json format
    fprintf(dump_file, "{\n");
    // partition size
    fprintf(dump_file, "\t\"partition_size\": %d,\n", fs->partition_size);
    // record the root structure
    int ret = record_root_in_dump_simple(fs, fs->root, dump_file);
    // end the bracket
    fprintf(dump_file, "}\n");
    fclose(dump_file);
    return ret;
}