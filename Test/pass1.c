/*
Check start for locctr
while not eof:
a) check if label is not **, push symtab
b)check opcode validity
c)check if opccode is anything as RESB,RESW,BYTE,WORD 
*/

#include<stdio.h>
#include<conio.h>
#include<string.h>

int main()
{
	// input file declarations
	char label[10],opcode[10],operand[10];
	// optab
	char mnemonic[10],code[10];
	// location counter
	int locctr=0;
	// file pointers
	FILE *inp,*out,*optab,*sym;
	// file initialisation
	inp=fopen("inputPass1.txt","r");
	out=fopen("outputPass1.txt","w");
	sym=fopen("symtab.txt","w");
	
	// read 1st inp line
	fscanf(inp,"%s%s%s",label,opcode,operand);
	// check for first line if start or not
	if(strcmp(opcode,"START")==0)
	{
		// get location counter
		locctr=atoi(operand);
		fprintf(out,"\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(inp,"%s%s%s",label,opcode,operand);
	}
	else
		locctr=0;
	
	// do till end of while in input file
	while(!feof(inp))
	{
		// print location counter
		fprintf(out,"%d",locctr);
		
		// check if anything in label field
		if(strcmp(label,"**")!=0)
		{
			fprintf(sym,"%s\t%d\n",label,locctr);
		}
		
		// check for validity of opcode
		// open optab.txt
		fscanf(optab,"%s%s",mnemonic,code);
		//checking area
		while(!feof(optab))
		{
			if(strcmp(opcode,mnemonic)==0)
			{
				locctr+=3;
				break;
			}
			fscanf(optab,"%s%s",mnemonic,code);
		}
		rewind(optab);
		
		
		// check for variable declarations
		if(strcmp(opcode,"RESB")==0)
		{
			locctr+=atoi(operand);
		}
		if(strcmp(opcode,"WORD")==0)
		{
			locctr+=3;
		}
		if(strcmp(opcode,"RESW")==0)
		{
			locctr+=(3*(atoi(operand)));
		}
		if(strcmp(opcode,"BYTE")==0)
		{
			locctr+=(strlen(operand)-3);
		}
		
		//Print the output 
		fprintf(out,"\t%s\t%s\t%s\n",label,opcode,operand);
		// Scan the next input
		fscanf(inp,"%s%s%s",label,opcode,operand);
	}
	
	fclose(inp);
	fclose(out);
	fclose(sym);
	printf("Pass 1 is done");
	getch();
	return 0;
}
