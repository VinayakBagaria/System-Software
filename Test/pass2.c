/*
check for start, print the line if found
check for declarations, if not continue
a)check and strip operand till ,X..
b)get opcode from optab
c)get addr from symtab
d)print the obj code
Print all the rest of the lines from declarations as it is
*/

#include<stdio.h>
#include<conio.h>
#include<string.h>

int main()
{
	// input file for pass 2 = output file of pass 1
	char inst_add[10],label[10],opcode[10],operand[10];
	//optab
	char mnemonic[10],code[10];
	// symtab
	char lab_name[10],lab_addr[10];
	// file pointers
	FILE *inp,*sym,*out,*optab;
	inp=fopen("outputPass1.txt","r");
	out=fopen("outputPass2.txt","w");
	
	printf("%c",getc(inp));
	// scan first line of input for start
	fscanf(inp,"%s%s%s",label,opcode,operand);
	if(strcmp(opcode,"START")==0)
	{
		fprintf(out,"\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(inp,"%s%s%s%s",inst_add,label,opcode,operand);	
	}
	
	// while not declarations are seen
	while((strcmp(opcode,"WORD")!=0)&&(strcmp(opcode,"RESW")!=0)&&(strcmp(opcode,"BYTE")!=0)&&(strcmp(opcode,"RESB")!=0))
	{
		// get the name of the symbol if ,X exists in it
		char get_name[10];
		int i=0;
		if(strstr(operand,",X")==0)
		{
			for(i=0;i<strlen(operand);i++)
			{
				if(operand[i]==',')
					break;
				get_name[i]=operand[i];
			}
		}
		else
			strcpy(get_name,operand);
		
		// get opcode's code from optab
		optab=fopen("optab.txt","r");
		fscanf(optab,"%s%s",mnemonic,code);
		while(!feof(optab))
		{
			if(strcmp(opcode,mnemonic)==0)
			{
				break;
			}
			fscanf(optab,"%s%s",mnemonic,code);
		}
		fclose(optab);
		
		// get symbol's address from symtab
		sym=fopen("symtab.txt","r");
		fscanf(sym,"%s%s",lab_name,lab_addr);
		while(!feof(sym))
		{
			if(strcmp(lab_name,get_name)==0)
			{
				break;
			}
			fscanf(sym,"%s%s",lab_name,lab_addr);
		}
		fclose(sym);
		
		// if X exists then add 8 to 1st bit
		if(strstr(operand,",X")==0)
		{
			if(lab_addr[0]=='0')
				lab_addr[0]='8';
			else if(lab_addr[0]=='1')
				lab_addr[0]='9';
			else if(lab_addr[0]=='2')
				lab_addr[0]='A';
			else if(lab_addr[0]=='3')
				lab_addr[0]='B';
			else if(lab_addr[0]=='4')
				lab_addr[0]='C';
			else if(lab_addr[0]=='5')
				lab_addr[0]='D';
			else if(lab_addr[0]=='6')
				lab_addr[0]='E';
			else
				lab_addr[0]='F';
		}
		
		// print the output
		fprintf(out,"%s\t%s\t%s\t%s\t%s-%s\n",inst_add,label,opcode,operand,code,lab_addr);
		// get the next line
		fscanf(inp,"%s%s%s%s",inst_add,label,opcode,operand);
	}
	
	// print rest of the lines
	while(!feof(inp))
	{
		// print the output
		fprintf(out,"%s\t%s\t%s\t%s\n",inst_add,label,opcode,operand);
		// get the next line
		fscanf(inp,"%s%s%s%s",inst_add,label,opcode,operand);
	}
	
	fclose(inp);
	fclose(out);
	printf("Pass 2 is done");
	getch();
	return 0;
}
