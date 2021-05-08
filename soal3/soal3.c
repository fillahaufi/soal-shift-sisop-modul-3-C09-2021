#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

pthread_t tid[101];
char temp[1024];

int is_file(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    int ans = S_ISREG(path_stat.st_mode);
    return ans;
}

int is_folder(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    int ans = S_ISDIR(path_stat.st_mode)
    return ans;
}

int main(int argc, char *argv[]) {
    getcwd(temp, sizeof(temp));
    
    int i;
    
    if(strcmp(argv[1], "-f") == 0)
    {
    	for(i = 2; i < argc; i++)
    	{
    	    if(is_file(argv[i]))
    	    {
    	    
    	    }
    	}
    	for(i = 0; i < argc - 2; i++)
    	{
    	
    	}
    }
    else if(strcmp(argv[1], "-d") == 0)
    {
    	for(i = 2; i < argc; i++)
    	{
    	   if(is_folder(argv[i]))
    	    {
    	    
    	    }
    	}
    	for(i = 0; i < argc - 2; i++)
    	{
    	
    	}
    }
    else if(strcmp(argv[1], "\*") == 0)
    {
    
    }
    
    return 0;
}
