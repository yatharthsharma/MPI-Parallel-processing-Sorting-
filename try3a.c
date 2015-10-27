#include "mpi.h"
#include <stdio.h>
#include<time.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
int wc=0;



int count_val()
{
	float linet,line1t,line2t,line3t;
	char line[10],line1[10],line2[10],line3[10];
	FILE *f;
	int count;	


	system("sar -P ALL 1 1| cut -c 76-85| head -8| tail -4 >out6.txt");
	f=fopen("out6.txt","r");
	count=0;

	while(!feof(f))	 
  	{
	fgets(line,10,f);
	break;
  	}

	while(!feof(f))
  	{
	fgets(line1,10,f);
	break;
  	}

	while(!feof(f))	 
 	{
	fgets(line2,10,f);
	break;
 	}


	while(!feof(f))	 
 	{
	fgets(line3,10,f);
	break;
 	}


	linet=atoi(line);
	printf("\n core 0 ideal : %f",linet);

	line1t=atoi(line1);
	printf("\n core 1 ideal : %f",line1t);


	line2t=atoi(line2);
	printf("\n core 2 ideal : %f",line2t);

	line3t=atoi(line3);
	printf("\n core 3 ideal : %f",line3t);


	if(linet>70)
	{
		printf("1 = %f",linet);
		count++;

	}

	if(line1t>70)
	{
		printf("2 =%f",line1t);
		count++;
	}


	if(line2t>70)
	{
		printf("3 =%f",line2t);
		count++;
	}


	if(line3t>70)
	{
		printf("4 =%f",line3t);
		count++;
	}
	
	return count;

}//function closure



int main(int argc, char **argv)
{
//clock_t start, end;
double elapsed;

char ch;
char compile[50],execute[50];
int i,count=0,wait_q=0,n,fc=0,j=0,size,rank,wait[5]={0,0,0,0,0};

double startT, stopT;

  struct file1{
  char file2[20];
  int pri,intnse,coren;
              }f1[5],f2[5];
    




float startTime;
srand((unsigned)time(NULL)); 
   //start=clock();


while(fc<5)
{
	strcpy(f1[fc].file2,"nikita2");
//	f1[fc].pri=rand()%2; 
	f1[fc].intnse=1;
	fc+=2;
}

fc=1;



while(fc<5)
{
	strcpy(f1[fc].file2,"anuf1");
//	f1[fc].pri=rand()%2;
	f1[fc].intnse=0;
	fc+=2;
} 


//fc=0;

f1[0].pri=3;
f1[1].pri=4;
f1[2].pri=1;
f1[3].pri=2;
f1[4].pri=0;





//-------assigning coren ---------//
fc=0;

while(fc<5)
{
if(f1[fc].pri>2.5 && f1[fc].intnse==0)
   {
f1[fc].coren=2;
   }

if(f1[fc].pri>2.5 && f1[fc].intnse==1)
  {
f1[fc].coren=4;
  }

if(f1[fc].pri<2.5 && f1[fc].intnse==0)
  {
f1[fc].coren=1;
  }

if(f1[fc].pri<2.5 && f1[fc].intnse==1)
  {
f1[fc].coren=3;
  }
fc++;
}


fc=0;


while(1)
{

//------sar-------//
	count=count_val();
	printf(" \ncount=%d",count);
//------------chcking the priority and the arith intensivity---------------//
	printf("\ncoren------%d",f1[fc].coren);
	printf("\npriority------%d",f1[fc].pri);	
//..............................................................................	
		wait_q=wc;

if(wc!=0)

{

printf("\nEntered into the Waiting Loop \n  ");
n=0;
while(n!=wait_q)
{
		
		if(f2[n].pri>f1[n].pri && f2[n].coren<=count)
	{
		printf("\n Running the waiting queue");		
printf(" file name %s",f2[wc].file2);
		sprintf(execute,"mpiexec -n %d /home/yatharth/Desktop/%s.o & ",f2[wc].coren,f2[wc].file2);
		sprintf(compile,"mpicc -o %s.o %s.c &",f2[wc].file2,f2[wc].file2);
		n=system(compile);
		printf("\ncomplied.....");
		system(execute); 
		printf("\nrunning.....");
		wc--;
	}

	else
	n++;

count=count-f2[n].coren;
}//closure of while



}	//closure of if


//printf("\n OUT OF WAITING RUNNING !!!!! \n\n");
//.............................................................

 if(f1[fc].coren<=count)
	{
		printf("\n------------- in if------");


		sprintf(execute,"mpiexec -n %d /home/yatharth/Desktop/%s.o & ",f1[fc].coren,f1[fc].file2);
		sprintf(compile,"mpicc -o %s.o %s.c &",f1[fc].file2,f1[fc].file2);
		n=system(compile);
		printf("\ncomplied.....");
		system(execute); 
		count=count-f1[fc].coren;	
		printf("\nfc =--------  %d" ,fc);


		

	}

	else

	{
		printf("\n Running the waiting queue");		
		strcpy(f2[wc].file2,f1[fc].file2);
		f2[wc].pri=f1[fc].pri;
		f2[wc].coren=f1[fc].coren;
		f2[wc].intnse=f1[fc].intnse;
printf(" file name %s",f2[wc].file2);
		wc++;

	}

	fc++;

	
	if(fc==5 && count==4)
	{  
	break;
	}



}




return 0;
}

