#include "mpi.h"
#include <stdio.h>
#include<time.h>
#include<malloc.h>
#define num 16
 
#define MAX_PROCESSES 10

double startT, stopT;
	 
	double startTime;


int log_2(int x)
{
int i=0;
while(x!=1)
{
x=x/2;
i++;
}
return i;
}

int power(n,j)
{
int i,res=1;
	for(i=0;i<j;i++)
	{
		res=res*n;
	}
return res;
}

 
void merge( int*, int,int,int,int);

int main( int argc, char **argv )
{
    int rank,s,y, size, i,j;
int *array;
    //int A[10];
int *A;    
int res,no_of_proc,p;


//int B[4][4];
     //   int table[4][4];
    int k=0,x=0;
    int errors=0,lb1,lb,rb,le,re,re1,cb;
    int *combined_array;
 	 
	   
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

startT = MPI_Wtime();
no_of_proc=size;	
res=log_2(no_of_proc); 

	s=num/size;
p=no_of_proc;
//int *B = (int*)malloc(2*s*sizeof(int));
//int *C = (int*)malloc(2*s*sizeof(int));
//int *D = (int*)malloc(4*s*sizeof(int));
//int *E = (int*)malloc(4*s*sizeof(int));
	
	if(rank == 0)
	
	{
		  combined_array=(int*)malloc(num*sizeof(int));
				
		
		
	
	}

 
	srand((double) time(NULL));    

     
///printf("\n");  
      if (rank == 0)
	{
                   A =(int*)malloc(num*sizeof(int));
				
        k=num;

	 for ( i=0; i<num; i++)
                {
                   A[i] = k--;
				
		}
		//printf("\n");
		/*for ( i=0; i<num; i++)
                {
                   printf("\t%d",A[i]);
				
		}*/	
		
	}
	
array=(int*)malloc(s*sizeof(int));

        MPI_Scatter(A, s, MPI_INT,
                         array , s, MPI_INT, 0, MPI_COMM_WORLD);


	

//printf("\nrank=%d\n",rank);
//printf("array (before sort after distribuution)");
/*for(i=0;i<s;i++)
{
	printf("\t%d",array[i]);
}
*/	
for(i=0;i<s;i++)
{	
	for(j=0;j<(s-i-1);j++)
	{
	if(array[j]>array[j+1])
	{
		k=array[j];
		array[j]=array[j+1];
		array[j+1]=k;
			
	}	
	}
	
}
	


//printf("\nrank= %d\n",rank);
//printf("\narray(after sort after distribution)\n");

/*for(i=0;i<s;i++)
{
	
	printf(" %d ,",array[i]);
	
}*/

	MPI_Gather(array,s,MPI_INT,combined_array,s,MPI_INT,0,MPI_COMM_WORLD);

if(rank==0)
{
	//printf("\nafter gather- combined array \n");


//if(rank==0)
	/*for(i=0;i<num;i++)
	{	
	printf("%d ,",combined_array[i]);
	} */
	
	//printf("\nMerging the Individually Sorted Arrays  \n");




for(j=0;j<res;j++)
{
	for(i=0;i<p/2;i++)
	{
		y=(j+1)*i *2*s;	
		
		merge(combined_array,y,y+power(2,j)*s-1, y+power(2,j)*s, y+2*power(2,j)*s-1);	
	}

	//printf("\nafter %d iteration\n",j);

	/*for(k=0;k<num;i++)
	{	
	printf("\t%d ,",combined_array[k]);
	} */
	

	p=p/2;
}








//printf("\n Final Completion of the Compiled array is :\n");



/*for(i=0;i<num;i++)
	{	
	printf("\n\t%d ,",combined_array[i]);
	} 
*/	
}

/*
for(k=lb1;k<=re1;k++)
{
	combined_array[k]=c_array[k];
}
*/
//printf("\n Combined Gathered Array after merging individually sorted array : \n");
if(rank==0)
{
    stopT = MPI_Wtime();
     printf("time = %f secs\n", (stopT-startT));
 }	MPI_Finalize();
    	return errors;

}



void merge( int* combined_array, int lb,int le,int rb,int re)
{

	/*lb1=lb=0;*/
	 int cb=0;
/*
	le=4;
	rb=5; re1=re=9;*/

int lb1=lb;
int re1=re;
int size=(re-lb)+1,i=0,k=0;
int *c_array=(int*)malloc(size*sizeof(int));

while((lb<=le) &&  (rb<=re))
{

	if(combined_array[lb]<combined_array[rb])
	{
	c_array[cb]=combined_array[lb++];
        cb++;
        }
	else
	{
	c_array[cb]=combined_array[rb++];
	cb++;
	}
}

if( rb<=re)
{
	while(rb<=re)
	c_array[cb++]=combined_array[rb++];
}

else
{

	while(lb<=le)
	c_array[cb++]=combined_array[lb++];
}
  
for(i=lb1;i<=re1;i++)
{

	combined_array[i]=c_array[k];
	k++;
}

}
