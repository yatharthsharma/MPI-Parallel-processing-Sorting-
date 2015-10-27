#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<sched.h>

//#define _GNU_SOURCE




/* this method will create threads. then bind each to its own cpu*/


void do_cpu_stress(int numthreads)
{
	//bool ret ;
	int created_thread =0 ;
	cpu_set_t mask;


	/* We need a thread for each cpu we have..*/
	while( created_thread < numthreads-1)
	{
	
	int mypid = fork();
	

	if( mypid == 0) /* child process*/
	{

          printf("\tCreating Child Thread: #%i\n", created_thread);
	//ret=TRUE;	
          break;

      }



      else if(mypid > 0)/* Only parent executes this */

      {

          /* Continue looping until we spawned enough threads! */ ;

          created_thread++;
	printf("\ncreated threads incremented! value : %d  \n",created_thread);	
	//ret= TRUE;

      }

	else
	{
		printf("Failure!!! ");
		//ret=FALSE;
	}

   	}

//setting CPU affinity now 

	


   /* CPU_ZERO initializes all the bits in the mask to zero. */

        CPU_ZERO( &mask );



   /* CPU_SET sets only the bit corresponding to cpu. */

        CPU_SET( created_thread, &mask );



   /* sched_setaffinity returns 0 in success */

        if( sched_setaffinity( 0, sizeof(mask), &mask ) == -1 )

   {

      printf("WARNING: Could not set CPU Affinity, continuing...\n");

   }

	else
	
	
	printf( "\n CPU affinity set !! ");


}

int main()
{

pid_t pid = getpid();
printf("\n pid is : %d \n", pid ); 	
	do_cpu_stress(10);
	//printf(" threads created: true if created or false if not created!!=  %s",rett);	
	return 0;


}
