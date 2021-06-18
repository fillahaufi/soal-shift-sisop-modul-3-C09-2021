#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <syslog.h>

pthread_t tid[101];

typedef struct args_struct {
    char asal[501];
    char cwd[501];
} args_struct;

int flag =1

//mengecek apakah itu file
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

void movefileF(char *argv, char *cwd) {
    int hiddenfile = 0;
    char string[500];
    strcpy(string, argv);

    //membaca file
    int isfile = is_file(string);
    char* tipe = strrcher(string, '.');
    char* nama = strrcher(string, '/');

    if(nama[1] == '.') {
        hiddenfile = 1; //hidden file
    }

    //lowercharacter
    char tipeLow[100];
    if(tipe) {
        strcpy(tipeLow, tipe);

        for(int i = 0; tipeLow[i]; i++) {
            tipeLow[i] = tolower(tipeLow[i]);
        }
    }
    else {
        if(!isfile) {
            printf("Ini adalah folder\n");
            return;
        }
        else {
            strcpy(tipeLow, " Unknown"); //Tidak ada ekstensi
        }
    }

    if(hiddenfile) {
        strcpy(tipeLow, " Hidden");
    }
    
    mkdir((tipeLow + 1), 0777); //Folder dengan ekstensi

    size_t len = 0;
    char a[1001];
    strcpy(a, argv);
    char b[1001];
    strcpy(b, cwd);
    strcat(b, "/");
    strcat(b, tipeLow+1);
    strcat(b, nama);
    if(!rename(a,b)) {
        printf("Berhasil Dikategorikan\n");
    }
    else {
        printf("Sad, Gagal :(\n");
    }
    remove(a);

}

void movefileD(char *argv, char *cwd) {
    int hiddenfile = 0;
    char string[500];
    strcpy(string, argv);

    //membaca file
    int isfile = is_file(string);
    char* tipe = strrcher(string, '.');
    char* nama = strrcher(string, '/');

    if(nama[1] == '.') {
        hiddenfile = 1; //hidden file
    }

    //lowercharacter
    char tipeLow[100];
    if(tipe) {
        strcpy(tipeLow, tipe);

        for(int i = 0; tipeLow[i]; i++) {
            tipeLow[i] = tolower(tipeLow[i]);
        }
    }
    else {
        if(!isfile) {
            printf("Ini adalah folder\n");
            return;
        }
        else {
            strcpy(tipeLow, " Unknown"); //Tidak ada ekstensi
        }
    }

    if(hiddenfile) {
        strcpy(tipeLow, " Hidden");
    }
    
    mkdir((tipeLow + 1), 0777); //Folder dengan ekstensi

    size_t len = 0;
    char a[1001];
    strcpy(a, argv);
    char b[1001];
    strcpy(b, cwd);
    strcat(b, "/");
    strcat(b, tipeLow+1);
    strcat(b, nama);
    if(!rename(a,b)) {
        flag = 0;
    }
    remove(a);

}

void *fcommmand(void* arg) {
    args_struct args = *(args_struct*) arg;
    movefileF(args.asal, args.cwd);
    pthread_exit(0);
}

void *dcommmand(void* arg) {
    args_struct args = *(args_struct*) arg;
    movefileD(args.asal, args.cwd);
    pthread_exit(0);
}

void sortfile(char *asal) {
    args_struct args;
    flag = 1;
    strcpy(args, "/home/naufaldillah/modul3");
    DIR *dirp;
    struct dirent *entry;
    dirp = opendir(asal);
    int index = 0;
    while((entry = readdir(dirp)) != NULL) {
        if(entry->d_type == DT_REG) {
            char filename[305];
            sprintf(filename, "%s/%s", asal, entry->d_name);
            strcpy(args.asal, filename);

            if(strcmp(filename, "/home/naufaldillah/modul3/soal3.c") != 0) {
                pthread_create(&tid[index], NULL, dcommmand, (void *)&args);
                printf("%s\n", filename);
                sleep(1);
                index++;
            }
        }
    }

    int(!flag) {
        printf("Yah gagal disimpan\n";)
    }
    else {
        printf("Direktori sudah disimpan\n")
    }
}

int main(int argc, char *argv[]) {
    args_struct args;
    getcwd(args.cwd, sizeof(args.cwd));
    
    int i;
    
    if(strcmp(argv[1], "-f") == 0)
    {
        int count = 0;
    	for(i = 2; i < argc; i++)
    	{
    	    if(is_file(argv[i]))
    	    {
                strcpy(args.asal, argv[i]);

                //membuat thread
                pthread_create(&tid[count], NULL, fcommand, (void *)&args);
                sleep(1);
                count++;
    	    }
    	}
    	for(i = 0; i < count; i++)
    	{
            pthread_join(tid[i], NULL);
    	}
    }
    else if(strcmp(argv[1], "-d") == 0)
    {
    	char asal[1001];
        strcpy(asal, argv[2]);
        sortfile(asal);
    }
    else if(strcmp(argv[1], "*") == 0)
    {
        char asal = "/home/naufaldillah/modul3";
        sortfile(asal);
    }
    else {
        printf("Argumen Invalid");
        return 0;
    }
    
    return 0;
}
