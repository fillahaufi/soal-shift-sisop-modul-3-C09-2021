# soal-shift-sisop-modul-3-C09-2021
# Laporan Resmi Modul 3 #

## Soal 1 ##
### Pengerjaan ###
#### Soal 1a. ####


## Soal 2 ##
### Pengerjaan ###
#### Soal 2a. ####
1. Diminta untuk membuat program perkalian matrix (4x3 dan 3x6) menggunakan thread
2. Source code berisi input matriks dan algoritma perkalian matriks:
```
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX 6

void *multipl(void* arg)
{
	int *data = (int *)arg;
	int k = 0, i = 0;
	
	int x = data[0];
	for (i = 1; i <= x; i++)
		k += data[i]*data[i+x];
	
	int *p = (int*)malloc(sizeof(int));
	*p = k;
	
	pthread_exit(p);
}

int main()
{

	int matA[MAX][MAX];
	int matB[MAX][MAX];
	
	
	int r1=4, c1=3, r2=3, c2=6;
    int i, j, k;

	printf("input matriks A : \n");
	for (i = 0; i < r1; i++) {
        for (j = 0; j < c1; j++)
			scanf("%d", &matA[i][j]);
            // matA[i][j] = rand() % 21;
    }
    
	printf("\ninput matriks B : \n");
	for (i = 0; i < r2; i++) {
        for (j = 0; j < c2; j++)
			scanf("%d", &matB[i][j]);
            // matB[i][j] = rand() % 21;
    }
	
    // printf("Matriks A : \n");
	// for (i = 0; i < r1; i++){
	// 	for(j = 0; j < c1; j++)
	// 		printf("%d ",matA[i][j]);
	// 	printf("\n");
	// }
    // printf("\n");
			
    // printf("Matriks B : \n");
	// for (i = 0; i < r2; i++){
	// 	for(j = 0; j < c2; j++)
	// 		printf("%d ",matB[i][j]);
	// 	printf("\n");	
	// }
    // printf("\n");
	
	int max = r1*c2;
		
	pthread_t *threads;
	threads = (pthread_t*)malloc(max*sizeof(pthread_t));
	
	int count = 0;
	int* data = NULL;
	for (i = 0; i < r1; i++) {
		for (j = 0; j < c2; j++) {
            data = (int *)malloc((20)*sizeof(int));
            data[0] = c1;

            for (k = 0; k < c1; k++)
                data[k+1] = matA[i][k];

            for (k = 0; k < r2; k++)
                data[k+c1+1] = matB[k][j];
            
            pthread_create(&threads[count++], NULL, multipl, (void*)(data));
            
        }
    }
	
	printf("\nMatriks A x Matriks B : \n");
	for (i = 0; i < max; i++)
	{
        void *k;
    
        pthread_join(threads[i], &k);
                
        int *p = (int *)k;
        printf("%d ",*p);
        if ((i + 1) % c2 == 0)
            printf("\n");
	}

	printf("\n");

    return 0;
}
```
3. Output :

![image](https://user-images.githubusercontent.com/63279983/119259225-70e05b80-bbf7-11eb-9213-87ac66e100db.png)

#### Soal 2b. ####
1. Diminta membuat program untuk mem faktorial matriks A (output dari soal2a) dan matriks B (input)
2. Source code :

#### Soal 2c. ####
1. Diminta membuat program untuk mengecek 5 proses teratas apa saja yang memakan resource komputer
2. Source code :


## Soal 3 ##
### Pengerjaan ###
#### Soal 3a. ####
1. Diminta untuk mengkategorikan file berdasarkan ekstensi untuk setiap argumen yang diberika oleh pengguna jika program menerima opsi -f
2. Source code:
```
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
```
mengecek apakah argumen yang diberikan adalah file:
```
int is_file(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    int ans = S_ISREG(path_stat.st_mode);
    return ans;
}
```

fcommand:
```
void *fcommmand(void* arg) {
    args_struct args = *(args_struct*) arg;
    movefileF(args.asal, args.cwd);
    pthread_exit(0);
}
```
movefileF:
```
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
```

#### Soal 3b. ####
1. Diminta untuk mengkategorikan file dalam folder yang diberikan oleh user.
2. Source Code:
```
else if(strcmp(argv[1], "-d") == 0)
    {
    	char asal[1001];
        strcpy(asal, argv[2]);
        sortfile;
    }
```

sortfile:
```
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
```

dcommand:
```
void *dcommmand(void* arg) {
    args_struct args = *(args_struct*) arg;
    movefileD(args.asal, args.cwd);
    pthread_exit(0);
}
```

movefileD:
```
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
```

#### Soal 3c. ####
1. Diminta untuk mengkategorikan file di working directory.
2. Source code:
```
else if(strcmp(argv[1], "*") == 0)
    {
        char asal = "/home/naufaldillah/modul3";
        sortfile(asal);
    }
```

#### Soal 3d. ####
1. Jika file tidak memiliki ekstensi, maka file disimpan dalam folde "Unknown"
```
else {
        if(!isfile) {
            printf("Ini adalah folder\n");
            return;
        }
        else {
            strcpy(tipeLow, " Unknown"); //Tidak ada ekstensi
        }
    }
```
2. Jika file hidden, maka file disimpan dalam folder "Hidden"
```
if(hiddenfile) {
        strcpy(tipeLow, " Hidden");
    }
```
#### Soal 3e. ####
Setiap satu file dikategorikan dioperasikan oleh 1 thread agar bisa secara parallel sehingga proses kategori bisa berjalan cepat
