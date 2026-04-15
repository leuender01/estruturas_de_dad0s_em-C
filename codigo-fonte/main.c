#include <stdio.h>
#include "merge_sort.h"

int main(void){
    int array[20]={
        24,32,10,2,61,5,3,2,56,4,5,23,45,542,0,90,36,81,21,42
    };
    int len = sizeof(array)/ sizeof(array[0]);
    merge_sort(array, 0, len - 1);
}