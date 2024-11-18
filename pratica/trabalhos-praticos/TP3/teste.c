#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
    char str1[] = "Carlos Alberto";
    char str2[] = "Carlos Gomes";
    int int1 = strcmp(str1, str2);
    printf("int1: %d\n", int1);
}