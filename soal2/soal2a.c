#include<stdio.h>
#include<pthread.h>
#include<sys/ipc.h>
#include<sys/shm.h>
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
	key_t key = 4121;
    	int shmid = shmget(key, 512, IPC_CREAT | 0666);
	void* memory = shmat(shmid, NULL, 0);
   	long long (*A)[6] = memory;
	
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
