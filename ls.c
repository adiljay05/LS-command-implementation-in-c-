#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include<sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

int a=0;
extern int errno;
int contains(char *options,char op)
{
    int i=0;
    //printf("contains function\n");
    while(options[i]!='\0')
    {
        if(options[i]==op)
            return 1;
        i++;
    }
  return 0;
}
void detailed(char *dir,char *arr,int size)
{
    struct dirent * entry;
    DIR * open = opendir(dir);
    struct stat info;

    char str[10];
    strcpy(str, "---------");

    errno = 0;
    while((entry = readdir(open)) != NULL)
    {

        int rv = lstat(entry->d_name, &info);

        int mode = info.st_mode; 
        if(entry == NULL && errno != 0)
        {
            perror("readdir failed");
            exit(1);
        }
        else{
            if(entry->d_name[0] == '.' && !contains(arr,'a'))
                continue;
            else
            {
                if((mode & 00000400) == 00000400) str[0] = 'r';
                if((mode & 00000200) == 00000200) str[1] = 'w';
                if((mode & 00000100) == 00000100) str[2] = 'x';
    //group permission0s
                if((mode & 00000040) == 00000040) str[3] = 'r';
                if((mode & 00000020) == 00000020) str[4] = 'w';
                if((mode & 00000010) == 00000010) str[5] = 'x';
    //others  permissions
                if((mode & 00000004) == 00000004) str[6] = 'r';
                if((mode & 00000002) == 00000002) str[7] = 'w';
                if((mode & 00000001) == 00000001) str[8] = 'x';
    //special  permissions
                if((mode & 00004000) == 00004000) str[2] = 's';
                if((mode & 00002000) == 00002000) str[5] = 's';
                if((mode & 00001000) == 00001000) str[8] = 't';

                
                if ((mode &  00170000) == 00040000 && contains(arr,'d')) 
                {
                    if(contains(arr,'i'))
                    {
                        int inode=info.st_ino;
                        printf("%d ", inode);
                    }
                    printf("d");
                    printf("%s ", str);
                    printf("%ld ", info.st_nlink);
                    if(contains(arr,'n'))
                    {
                        printf("%d ",info.st_uid);
                    }
                    else
                    {
                        struct passwd * pwd = getpwuid(info.st_uid);
                        printf("%s ", pwd->pw_name);
                    }
                    if(contains(arr,'n'))
                    {
                        printf("%d ", info.st_gid);
                    }
                    else
                    {
                        struct group * grp = getgrgid(info.st_gid);
                        printf("%s ", grp->gr_name);
                    }

                    if(contains(arr,'h'))
                    {
                        long int size1=info.st_size;
                        char array1[4][2]={"KB","MB","GB","TB"};
                        int j=0;
                        while(size1>1024)
                        {
                            size1/=1024;
                            j++;
                        }
                        printf("%ld.00%c%c ",size1,array1[j][0],array1[j][1] );
                    }
                    else
                        printf("%ld\t", info.st_size);

                    if(contains(arr,'c'))
                    {
                        char *val=ctime(&info.st_ctime);
                        int i=0;
                        while(val[i]!='\0')
                            i++;
                        val[--i]='\0';
                        printf("%-15.12s ", val);
                    }
                    else if(contains(arr,'u'))
                    {
                        char *val=ctime(&info.st_atime);
                        int i=0;
                        while(val[i]!='\0')
                            i++;
                        val[--i]='\0';
                        printf("%-15.12s ", val);
                    }
                    else
                    {
                        char *val=ctime(&info.st_mtime);
                        int i=0;
                        while(val[i]!='\0')
                            i++;
                        val[--i]='\0';

                        printf("%-15.12s ", val);
                    }
         
                    if ( info.st_mode & S_IXUSR)
                        printf("\033[1;32m");
                    if ((mode &  0170000) == 0040000) 
                        printf("\033[1;34m");
                    if ((mode &  170000) == 120000)
                        printf("\033[1;36m");
                    printf("%s\n", entry->d_name );
                    printf("\033[0m");
                }
                else if(!contains(arr,'d'))
                {
                    if(contains(arr,'i'))
                    {
                        int inode=info.st_ino;
                        printf("%d ", inode);
                    }
                    if ((mode &  0170000) == 0010000) 
                        printf("p");
                    else if ((mode &  0170000) == 0020000) 
                        printf("c");
                    else if ((mode &  0170000) == 0040000) 
                        printf("d");
                    else if ((mode &  0170000) == 0060000) 
                        printf("b");
                    else if ((mode &  0170000) == 0100000) 
                        printf("-");
                    else if ((mode &  0170000) == 0120000) 
                        printf("l");
                    else if ((mode &  0170000) == 0140000) 
                        printf("s");
          
                    printf("%s ", str);
                    printf("%ld ", info.st_nlink);
                    if(contains(arr,'n'))
                    {
                        printf("%d ",info.st_uid);
                    }
                    else
                    {
                        struct passwd * pwd = getpwuid(info.st_uid);
                        printf("%s ", pwd->pw_name);
                    }
                    if(contains(arr,'n'))
                    {
                        printf("%d ", info.st_gid);
                    }
                    else
                    {
                        struct group * grp = getgrgid(info.st_gid);
                        printf("%s ", grp->gr_name);
                    }

                    if(contains(arr,'h'))
                    {
                        long int size1=info.st_size;
                        char array1[4][2]={"KB","MB","GB","TB"};
                        int j=0;
                        while(size1>1024)
                        {
                            size1/=1024;
                            j++;
                        }
                        printf("%ld.00%c%c ",size1,array1[j][0],array1[j][1] );
                    }
                    else
                        printf("%5ld ", info.st_size);

                    char *val=ctime(&info.st_mtime);
                    int i=0;
                    while(val[i]!='\0')
                        i++;
                    val[--i]='\0';

                    printf("%-15.12s ", val+4);
         
                    if ( info.st_mode & S_IXUSR)
                        printf("\033[1;32m");
                    if ((mode &  0170000) == 0040000) 
                        printf("\033[1;34m");
                    if ((mode &  170000) == 120000)
                        printf("\033[1;36m");
                   int u=0;
                    while(entry->d_name[u]!='\0')
                    {
                        if(entry->d_name[u]=='.' && entry->d_name[u+1]=='t' && entry->d_name[u+2]=='a' && entry->d_name[u+3]=='r' || 
                        	entry->d_name[u]=='.' && entry->d_name[u+1]=='g' && entry->d_name[u+2]=='z' ||
                            entry->d_name[u]=='.' && entry->d_name[u+1]=='z' && entry->d_name[u+2]=='i' && entry->d_name[u+3]=='p'){
                            printf("\033[1;31m");
                            break;
                        }
                        u++;
                    }
                    u=0;
                    while(entry->d_name[u]!='\0')
                    {
                        if(entry->d_name[u]=='.' && entry->d_name[u+1]=='j' && entry->d_name[u+2]=='p' && entry->d_name[u+3]=='g' || entry->d_name[u]=='.' && entry->d_name[u+1]=='p' && entry->d_name[u+2]=='n' && entry->d_name[u+3]=='g' || entry->d_name[u]=='.' && entry->d_name[u+1]=='j' && entry->d_name[u+2]=='p' && entry->d_name[u+3]=='e' &&entry->d_name[u+4]=='g'){
                            printf("\033[1;35m");
                            break;
                        }
                        u++;
                    }

                    if((mode & 00000002) == 00000002 && (mode &  0170000) == 0040000) {
                        printf("\033[1;42m\33[1;34m%s\033[0m\n",entry->d_name);
                        printf("\033[0m");
                    }
                    	
                    else {
                    	printf("%s\n", entry->d_name );
                    }
                    printf("\033[0m");

                }
            }
        }
        strcpy(str, "---------");
    } 
    printf("\n");
    closedir(open);      
}


void shortInfo(char * dir,char *arr,int s)
{
    struct dirent * entry;
    DIR * dp = opendir(dir);
    if (dp == NULL){
        fprintf(stderr, "ls: Cannot access '%s' No such file or directory\n",dir);
        return;
    }
    errno = 0;
    struct stat info;
    while((entry = readdir(dp)) != NULL)
    {
        if(entry == NULL && errno != 0)
        {
            perror("readdir failed");
            exit(1);
        }
        else
        {
            if(entry->d_name[0] == '.' && a==0)
            continue;
        }
        lstat(entry->d_name, &info);
        if(contains(arr,'i'))
        {
            int inode=info.st_ino;
            printf("%d ", inode);
        }
        int mode=info.st_mode;
        if ( info.st_mode & S_IXUSR)
            printf("\033[1;32m");
        if ((mode &  0170000) == 0040000) 
            printf("\033[1;34m");
        if ((mode &  0170000) == 0120000)
            printf("\033[1;36m");
       int u=0;
        while(entry->d_name[u]!='\0')
        {
            if(entry->d_name[u]=='.' && entry->d_name[u+1]=='t' && entry->d_name[u+2]=='a' && entry->d_name[u+3]=='r' || 
                entry->d_name[u]=='.' && entry->d_name[u+1]=='g' && entry->d_name[u+2]=='z' ||
                entry->d_name[u]=='.' && entry->d_name[u+1]=='z' && entry->d_name[u+2]=='i' && entry->d_name[u+3]=='p'){
                printf("\033[1;31m");
                break;
            }
            u++;
        }
        u=0;
        while(entry->d_name[u]!='\0')
        {
            if(entry->d_name[u]=='.' && entry->d_name[u+1]=='j' && entry->d_name[u+2]=='p' && entry->d_name[u+3]=='g' || entry->d_name[u]=='.' && entry->d_name[u+1]=='p' && entry->d_name[u+2]=='n' && entry->d_name[u+3]=='g' || entry->d_name[u]=='.' && entry->d_name[u+1]=='j' && entry->d_name[u+2]=='p' && entry->d_name[u+3]=='e' &&entry->d_name[u+4]=='g'){
                printf("\033[1;35m");
                break;
            }
            u++;
        }

        if((mode & 00000002) == 00000002 && (mode &  0170000) == 0040000) {
            printf("\033[1;42m\33[1;34m%s\033[0m\t",entry->d_name);
            //printf("\033[0m");
        }
            
        else {
            printf("%s\t ", entry->d_name );
        }
        printf("\033[0m");
        if(contains(arr,'1'))
            printf("\n");
    }
    printf("\n");
    closedir(dp);
}



int main(int argc, char* argv[]){
    if (argc == 1){
        //printf("Directory listing of pwd:\n");
        shortInfo(".",argv[0],argc);
    }
    else{
        int i = 0,j=2;
        char *arr=argv[0];
        while(++i < argc){
            if(argv[1][0]=='-')
            {
                if(contains(argv[1],'l') || contains(argv[1],'n'))
                {
                    if(argv[2]==NULL)
                        detailed(".",argv[i],argc);
                    else
                        while(argv[j]!=NULL)
                        {
                            detailed(argv[j],argv[i],argc);
                            j++;
                        }
                }
                if(contains(argv[1],'a'))
                    a=1;
                if(argv[2]==NULL && !contains(argv[1],'l') && !contains(argv[1],'n'))
                    shortInfo(".",argv[i],argc);
                else
                    while(argv[j]!=NULL)
                    {
                        shortInfo(argv[j],argv[i],argc);
                        j++;
                    }
            }
            else
            {
                //printf("Directory listing of %s:\n", argv[i] );
                a=0;
                shortInfo(argv[i],argv[i],argc);
            }
        }
    }
    return 0;
}

