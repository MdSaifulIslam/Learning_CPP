#include<stdio.h>
#include<string.h>

int main(){

    int i, len, v_count=0, c_count=0, o_count=0;
    char arr[100];
    gets(arr);
    len = strlen(arr);

    for(i= 0; i<len || arr[i] != '\0'; i++){
        if(arr[i] >= 'A' && arr[i] <= 'Z'){
            c_count ++;
        }
        else if(arr[i] >= 'a' && arr[i] <= 'z'){
            c_count ++;
        }
        else{
            o_count ++;
        }
    }

    printf("total vowel : %d, total consonent : %d, others/special char: %d", v_count, c_count, o_count);

    return 0;
}