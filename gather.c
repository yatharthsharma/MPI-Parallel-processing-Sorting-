#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

void main(int argc, char ** argv)
{

int rank, size;
int * array, *combined_array;
int N,i;
char fname[20];
FILE * fp;

MPI_Init(&argc, &argv);

N = 10;
array = (int *)malloc(sizeof(int)*N);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);

printf("hello from %d of %d\n",rank, size);

if(rank == 0)
combined_array = (int *)malloc(sizeof(int)*N*size);

sprintf(fname,"%d.txt",rank);
fp = fopen(fname,"w");

for(i=0;i<N;i++)
{
array[i] = rank;
fprintf(fp,"%d\n",array[i]);
}
fclose(fp);

if(rank==0)
{
printf("before gather");
for(i=0;i<size*N;i++)
	printf("%d ",combined_array[i]);
printf("\n");
}

MPI_Gather(array,N,MPI_INT,combined_array,N,MPI_INT,0,MPI_COMM_WORLD);

if(rank==0)
{
printf("after gather");
if(rank==0)
for(i=0;i<size*N;i++)
	printf("%d ",combined_array[i]);
printf("\n");
}
MPI_Finalize();
}


