#include "mpi.h"
#include <stdio.h>
#include<time.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char **argv)
{
//clock_t start, end;
double elapsed;
FILE *f;
char ch;
char compile[50],execute[50];
int i,count=0,n,fc=0,j=0,size,rank,flag=0,k=0,wait[5]={0,0,0,0,0};
float linet,line1t,line2t,line3t;
char line[10],line1[10],line2[10],line3[10];

double startT, stopT;

  struct file1{
  char file2[20];
  int pri,intnse,coren;
              }f1[5];
    




float startTime;
 srand((unsigned)time(NULL)); 
   //start=clock();
while(fc<5)
  {
strcpy(f1[fc].file2,"nikita2");
f1[fc].pri=rand()%2; 
f1[fc].intnse=1;
fc+=2;
  }
fc=1;
while(fc<5)
  {
strcpy(f1[fc].file2,"anuf1");
f1[fc].pri=rand()%2;
f1[fc].intnse=0;
fc+=2;
   } 

//-------assigning coren ---------//
fc=0;

while(fc<5)
{
if(f1[fc].pri==0&&f1[fc].intnse==0)
   {
f1[fc].coren=1;
   }

if(f1[fc].pri==0&&f1[fc].intnse==1)
  {
f1[fc].coren=2;
  }

if(f1[fc].pri==1&&f1[fc].intnse==0)
  {
f1[fc].coren=1;
  }

if(f1[fc].pri==1&&f1[fc].intnse==1)
  {
f1[fc].coren=4;
  }
fc++;
}
fc=0;
while(1)
{

//------sar-------//
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
{printf("1 = %f",linet);
count++;

}
if(line1t>70)
{printf("2 =%f",line1t);
count++;
}
if(line2t>70)
{printf("3 =%f",line2t);
count++;
}
if(line3t>70)
{printf("4 =%f",line3t);
count++;
}
printf(" count=%d",count);
//------------chcking the priority and the arith intensivity---------------//
printf("coren------%d",f1[fc].coren);
if(f1[fc].coren<=count)
{printf("------------- in if------");
sprintf(execute,"mpiexec -n %d /home/yatharth/Desktop/%s.o & ",f1[fc].coren,f1[fc].file2);
sprintf(compile,"mpicc -o %s.o %s.c  &",f1[fc].file2,f1[fc].file2);
n=system(compile);
printf("complied.....");
system(execute); 
count=count-f1[fc].coren;
printf("fc =--------  %d" ,fc);

k=fc;
wait[k]=1;

fc++;
if(fc==5)
{

for(i=0;i<5;i++)
{  if(wait[i]==0)
	{
		fc=i;
		flag=1;
		break;
	}
   else
	flag=0;

}
if(flag==0)
	break;

}

}



else
{


fc++;
if(fc==5)
for(i=0;i<5;i++)
{
	if(wait[i]==0)
	{
		fc=i;
		flag=1;
		break;
	}
}

}



}



fclose(f);
return 0;
}

