/*
check if declarations exist
a)print location
b)push symbol on symtab
c)increase locctr a/ declarations

while not eof
a) print locctr
b) get addr from symtab
c) get code from optab
d) print obj code
*/

#include<stdio.h>
#include<conio.h>
#include<string.h>

int main()
{
	// input file for 1 pass
	char inst_add[10],label[10],opcode[10],operand[10];
	//optab
	char mnemonic[10],code[10];
	// symtab
	char lab_name[10],lab_addr[10];
	//location ctr
	int locctr=0;
	// file pointers
	FILE *inp,*sym,*out,*optab;
	inp=fopen("inputPass3.txt","r");
	out=fopen("outputPass3.txt","w");
	sym=fopen("symtab.txt","w");
	FILE *sym1;
	sym1=fopen("symtab.txt","r");
		
	// scan first line of input for start
	fscanf(inp,"%s%s%s",label,opcode,operand);
	if(strcmp(opcode,"START")==0)
	{
		// get location counter
		locctr=atoi(operand);
		fprintf(out,"\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(inp,"%s%s%s",label,opcode,operand);
	}
	else
		locctr=0;
	
	// while declarations are seen
	while((strcmp(opcode,"WORD")==0)||(strcmp(opcode,"RESW")==0)||(strcmp(opcode,"BYTE")==0)||(strcmp(opcode,"RESB")==0))
	{
		fprintf(out,"%d",locctr);
		//put it into symtab
		fprintf(sym,"%s\t%d\n",label,locctr);
		
		// increment location counters by checking declarations
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
	fclose(sym);
	
	// while not end of file where instructions are seen
	while(!feof(inp))
	{
		fprintf(out,"%d\t",locctr);
		
		// get opcode's code from optab
		optab=fopen("optab.txt","r");
		fscanf(optab,"%s%s",mnemonic,code);
		while(!feof(optab))
		{
			if(strcmp(opcode,mnemonic)==0)
			{
				locctr+=3;
				break;
			}
			fscanf(optab,"%s%s",mnemonic,code);
		}
		fclose(optab);
		
		// get symbol's address from symtab
		fscanf(sym1,"%s %s",lab_name,lab_addr);
		while(!feof(sym1))
		{
			if(strcmp(lab_name,operand)==0)
			{
				break;
			}
			fscanf(sym1,"%s %s",lab_name,lab_addr);
		}
		rewind(sym1);
		
		// print the object code here
		// print the output
		fprintf(out,"%s\t%s\t%s\t%s-%s\n",label,opcode,operand,code,lab_addr);
		// get the next line
		fscanf(inp,"%s%s%s",label,opcode,operand);
	}
	
	fclose(sym1);
	fclose(inp);
	printf("Pass 3 is done");
	getch();
	return 0;
}
