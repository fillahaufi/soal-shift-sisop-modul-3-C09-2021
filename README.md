# soal-shift-sisop-modul-3-C09-2021
# Laporan Resmi Modul 2 #

## Soal 1 ##
### Pengerjaan ###
#### Soal 1a. ####


## Soal 2 ##
### Pengerjaan ###
#### Soal 2a. ####
1. Diminta untuk membuat program perkalian matrix (4x3 dan 3x6) menggunakan thread
2. source code :
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
#### Soal 2c. ####

## Soal 3 ##
### Pengerjaan ###
#### Soal 3a. ####
Diminta mengkategorikan file berdasarkan argumen yang ditambahkan oleh pengguna jika program menerima opsi -f

#### Soal 3b. ####
Diminta mengkategorikan file di suatu directory yang diberikan oleh user jika program menerima opsi -d

#### Soal 3c. ####
Jika menerima opsi *, maka diminta untuk mengkategorikan file yang ada di owrking directory ketika menjalankan program c tersebut.

#### Soal 3d. ####
Jika file tidak memiliki ekstensi, maka file disimpan dalam folder "Unknown". Jika file hidden, masuk folder "Hidden"

#### Soal 3e. ####
Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread.
