#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

int fine(struct stat *objI, char *mod, int *modMasc, char *rwx, char *strtime, int *flags, char *push);

int main(int argc, char *argv[])
{
    int flags[2];
    for(int i = 1; i < argc; i++)
    {
        if(argv[i][0]=='-')
        for(int j = 1; j < strlen(argv[i]);j++)
        {
            switch (argv[i][j])
            {
            case 'l':
                flags[0] = 1;
                break;

            case 'a':
                flags[1] = 1;
                break;

            default:
                return 1;
            }
        }


    }    
    
    
    struct stat objI;
    char mod[10];
    mod[9]='\0';
    int modMasc[9] = {S_IROTH,S_IWOTH,S_IXOTH,S_IRGRP,S_IWGRP,S_IXGRP,S_IRUSR,S_IWUSR,S_IXUSR};
    char rwx[3] = {'r','w','x'};
    char strtime[100];
    
    int was = 1;
    for(int i = 1; i < argc; i++)
    if(argv[i][0]!='-')
    {
        if(fine(&objI, mod, modMasc, rwx, strtime, flags, argv[i]))
            return 1;
        was = 0;
    }
    if(was&&fine(&objI, mod, modMasc, rwx, strtime, flags, ".\0"))
        return 1;
    return 0;
}

int fine(struct stat *objI, char *mod, int *modMasc, char *rwx, char *strtime,int *flags, char *push)
{
    DIR *dirf;
    struct dirent *obj;
    dirf = opendir(push);
    while ((obj = readdir(dirf))!=NULL)
    {
        if((flags[1]||(obj->d_name[0]!='.')))
        {
            if(flags[0])
            {
                struct passwd *uid;
                struct group *gid;
                stat(obj->d_name, objI);
                for(int i = 0; i<9; i++){
                    if(objI->st_mode&modMasc[i])
                        mod[i] = rwx[i%3];
                    else
                        mod[i] = '-';
                }
                uid = getpwuid(objI->st_uid);
                gid = getgrgid(objI->st_gid);
                strftime(strtime,100,"%c", gmtime(&objI->st_mtim.tv_sec));
                printf("-%s %ld %s %s %li %s ", mod, objI->st_nlink, uid->pw_name, gid->gr_name, objI->st_size, strtime);
                switch(objI->st_mode&S_IFMT)
                {
                    case S_IFREG:
                        printf("%s\n", obj->d_name);
                        break;
                    case S_IXUSR://not work, i dont know why
                        printf("\033[32m%s\033[0m\n", obj->d_name);
                        break;
                    case S_IFDIR:
                        printf("\033[34m%s\033[0m\n", obj->d_name);
                        break;
                    case S_IFLNK:
                        printf("\033[36m%s\033[0m\n", obj->d_name);
                        break;
                    default:
                        return 1;
                }
            }
            else
            {
                stat(obj->d_name, objI);
                switch(objI->st_mode&S_IFMT)
                {
                    case S_IFREG:
                        printf("%s ", obj->d_name);
                        break;
                    case S_IXUSR://not work, i dont know why
                        printf("\033[32m%s\033[0m ", obj->d_name);
                        break;
                    case S_IFDIR:
                        printf("\033[34m%s\033[0m ", obj->d_name);
                        break;
                    case S_IFLNK:
                        printf("\033[36m%s\033[0m ", obj->d_name);
                        break;
                    default:
                        return 1;
                }
            }
        }
    }
    closedir(dirf);
    printf("\n");
    return 0;
}