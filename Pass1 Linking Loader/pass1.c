#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10

struct estab{
	char csect[10],sym_name[10];
	long int add;
	int length;
}table[MAX]; 

void main(){
	FILE *fp1,*fp2;
	char input[10];
	long int i,count=0,start,length,loc;
	fp1=fopen("dlinkin.txt","r");
	fp2=fopen("dlinkout.txt","w");
	
	// take starting address for loading the program
	printf("\nEnter the location where the program has to be loaded:"); 
	scanf("%lx",&start);
	// header decorations
	fprintf(fp2,"CSECT\tSymname\tAddress\tLength\n------------------------------\n");
	// start fp1 from beginning
	rewind(fp1); 
	
	while(!feof(fp1))
	{
		fscanf(fp1,"%s",input); 
		// H CSECT_NAME REF_START(6) LENGTH_DEC(6) 
		if(strcmp(input,"H")==0) 
		{
			// get control section name
			fscanf(fp1,"%s",input);
			strcpy(table[count].csect,input);
			// appending null to symbol name
			strcpy(table[count].sym_name,"\0");
			fscanf(fp1,"%s",input);
			table[count].add=atoi(input)+start;
			fscanf(fp1,"%s",input);
			length=atoi(input);
			table[count++].length=atoi(input);
			fscanf(fp1,"%s",input);
		}
		if(strcmp(input,"D")==0)
		{
			fscanf(fp1,"%s%lx",input,&loc);
			while((strcmp(input,"R")!=0))
			{
				strcpy(table[count].csect,"\0");
				strcpy(table[count].sym_name,input);
				table[count].add=loc+start;
				table[count++].length=0;
				fscanf(fp1,"%s%lx",input,&loc);
			} 
			while(strcmp(input,"T")!=0) 
				fscanf(fp1,"%s",input);
		}
		// get the end record for this control section
		if(strcmp(input,"T")==0) 
			while(strcmp(input,"E")!=0) 
				fscanf(fp1,"%s",input); 
		
		// get next line which is the header for next control section
		fscanf(fp1,"%s",input);
		start=start+length;
	}
	for(i=0;i<count;i++)
		fprintf(fp2,"%s\t%s\t%lx\t%d\n",table[i].csect,table[i].sym_name,table[i].add,table[i].length);
	
	printf("dlinkout.txt is created.");
	getch();
} 
