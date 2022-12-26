#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void find(char** ftxt, int size, FILE* file);
char** get_txtf(char* fname, int* i);

int main(int argc, char *argv[])
{
    if(argc<2)
        return 1;
    
    int f = 0;
    for(int i=1; i<argc; i++)
        if(argv[i][0]=='-'&&argv[i][1]=='f'&&argv[i][2]=='\0')
        {
            f = i+1;
            break;
        }


    
    if(((argc==2)||((argc==3)&&(f!=0)))&&(stdin!=NULL))
    {
        if(f)
        {
            int i;
            char** txtf;
            txtf = get_txtf(argv[f], &i);
            find(txtf,i,stdin);
        }
        else
            find(&argv[1],1,stdin);
    }
    else
    {
        FILE* file;
        if(f!=0)
        {
            int i;
            char** txtf = get_txtf(argv[f], &i);
            for(int j = 1; j<f-1; j++)
            {
                file = fopen(argv[j],"r");
                if(file == NULL)
                    return 1;
                find(txtf,i,file);
            }
            for(int j = f+1; j<argc; j++)
            {
                file = fopen(argv[j],"r");
                if(file == NULL)
                    return 1;
                find(txtf,i,file);
            }
        }
        else{
            for(int i=2; i<argc; i++)
            {
                file = fopen(argv[i],"r");
                if(file == NULL)
                    return 1;
                find(&argv[1],1,file);
            }
        }
        
    }
    return 0;
}

char** get_txtf(char* fname, int* i)
{
    FILE* file = fopen(fname,"r");
    char str[225];
    char** fstr = (char**)calloc(10,sizeof(char*));
    *i = 0;
    int n = 10;
    while (fgets(str,225,file)!=NULL)
    {
        if(*i>n)
        {
            n+=10;
            fstr = (char**)realloc(fstr,sizeof(char*)*n);
        }
        fstr[*i] = (char*)calloc(strlen(str)-(str[strlen(str)-1]=='\n'),sizeof(char));
        for(int j=0; j<strlen(str)-(str[strlen(str)-1]=='\n'); j++)
            fstr[*i][j] = str[j];
        (*i)++;
    }
    fstr = (char**)realloc(fstr,sizeof(char*)*(*i));
    return fstr;
}

void find(char** ftxt, int size, FILE* file)
{
    char strW[225];
    int strL[size];
    for(int i=0; i<size; i++)
        strL[i] = strlen(ftxt[i]);
    while (fgets(strW, 255, file) != NULL)
    {
        char *strf = strW;
        char *strff = NULL;
        int n;
        for(int i=0; i<size; i++){
            char* str = strstr(strf, ftxt[i]);
            if((str!=NULL)&&((str<strff)||(strff==NULL)))
            {
                strff = str;
                n = i;
            }
        }
        while(strff != NULL)
        {
            strff[0]='\0';
            strff = &strff[(strL[n])];
            printf("%s\033[1;31m%s\033[0m", strf, ftxt[n]);
            strf = strff;
            strff = NULL;
            for(int i=0; i<size; i++)
            {
                char* str = strstr(strf, ftxt[i]);
                if((str<strff)&&(str!=NULL))
                {
                    strff = str;
                    n = i;
                }
            }
            if(strff == NULL) printf("%s", strf);
        }
    }
    printf("\n");
}