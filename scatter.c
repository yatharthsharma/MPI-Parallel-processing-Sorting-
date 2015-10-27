#include "mpi.h"
#include <stdio.h>
#define SIZE 6

int main(int argc,char ** argv)
 {
int rank,numtasks;
//int numtasks, rank, sendcount, recvcount, source;
int sendbuf[SIZE] =  {1, 2, 3, 4,5,6};
  //{5.0, 6.0, 7.0, 8.0},
  //{9.0, 10.0, 11.0, 12.0},
  //{13.0, 14.0, 15.0, 16.0}  };
int recvbuf[(SIZE/2)];

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

  //source = 1;
  //sendcount = SIZE;
  //recvcount = SIZE;
  MPI_Scatter(sendbuf,2,MPI_INT,recvbuf,2,
             MPI_INT,0,MPI_COMM_WORLD);

  printf("rank= %d  Results: %d %d\n",rank,recvbuf[0],
         recvbuf[1]);

//else
  //printf("Must specify %d processors. Terminating.\n",SIZE);

MPI_Finalize();
}

