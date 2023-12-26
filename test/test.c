#include "test.h"
#include <stdio.h>

int test_get(){
    int ret = 0;
    ret = check_dump_folder();
    ret = create_dump_folder();
    return ret;
}

int test_put(){
    int ret = 0;
    return ret;
}

int test_rmdir(){
    int ret = 0;
    return ret;
}

void test_all(){
    printf("Testing get...");
    if(test_get()!=0){
        printf(RED"Test failed!\n"RESET);
        return;
    }
    printf(GREEN"OK\n"RESET);
    printf("Testing put...");
    if(test_put()!=0){
        printf(RED"Test failed!\n"RESET);
        return;
    }
    printf(GREEN"OK\n"RESET);
    printf("Testing rmdir...");
    if(test_rmdir()!=0){
        printf(RED"Test failed!\n"RESET);
        return;
    }
    printf(GREEN"OK\n"RESET);
    printf(GREEN"All tests passed!\n"RESET);
}

int main(void){
    test_all();
    return 0;
}