#include <stdio.h>

int main(){
    int array[] = {1,2,3,4,5,6,7,8,9}, cond=0;
    int len = (sizeof(array)/sizeof(int));
    int cop_len = len;
    for(int a=0; a<5; a++){
        for(int i =0 ; i<len ; i++){
            printf("%d",array[i]);
        };
        len--;
        puts("\n");
};
    return 0;
};