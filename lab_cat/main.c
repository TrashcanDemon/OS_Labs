#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#define STRSIZE 2048

int main(int argc, char* argv[]){
    char c;
    bool args[] = {false, false, false, false};        //0n,1b,2E,3s
    char str[STRSIZE];
    int linecount = 1;
    bool empty = false;

    FILE* file = fopen(argv[1], "r");
    if (file == NULL){
        printf("File not found. Please ensure that first argument is filename.\n");
        exit(1);
    };

    while ((c = getopt(argc, argv, "nbEs")) != -1){
        switch(c){
            case 'n':
                args[0] = true;
                break;
            case 'b':
                args[1] = true;
                args[0] = false;
                break;
            case 'E':
                args[2] = true;
                break;
            case 's':
                args[3] = true;
                break;
        }
    }
    
    while(fgets(str, STRSIZE, file) != NULL){
        if (str[1] == '\n'){                    //is empty?
            empty = true;
        }else{
            empty = false;
        }
        if(empty && args[3])                    //argument s
            continue;
        if ((args[0]) || (args[1]&&(!empty)))   //argument n or b
            printf("%d   ", linecount);
        if (args[2]){                            //argument E
            int len = strlen(str);
            str[len-2] = '$';
            str[len-1] = '\n';
        }
        printf("%s", str);                      //the string
        linecount++;                            //update linecount
    }
    fclose(file);
    return 0;
}