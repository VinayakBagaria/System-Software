#include<stdio.h>
#include<conio.h>
#include<string.h>

void main()
{

char opcode[10],mnemonic[3],operand[10],label[10],addr[10],code[10],add[10],label2[10],index[10];


FILE *fp1,*fp2,*fp3,*fp4;

// contains input program
fp1=fopen("out.txt","r");
// the output program with the assigned addresses
fp2=fopen("pass2ed.txt","w");
// the instruction/mnemonic table with the corresponding opcodes
fp3=fopen("symtbl.txt","r");
fp4=fopen("optab.txt","r");
// stores the first line in the corresponding 3 arrays
fscanf(fp1,"%s%s%s",code,opcode,operand);
// if START exists in 1st line

if(strcmp(opcode,"START")==0)
{
	fprintf(fp2,"\t%s\t%s\t%s\n",code,opcode,operand);
	fscanf(fp1,"%s%s%s%s",add,label2,opcode,operand);
}	

// while END exists in the line
while((strcmp(opcode,"RESW")!=0)&&(strcmp(opcode,"WORD")!=0)&&(strcmp(opcode,"RESB")!=0)&&(strcmp(opcode,"BYTE")!=0))
{	
	fp3=fopen("symtbl.txt","r");
	int i=0;
	
	if(strstr(operand,",X"))
	{
		for(i=0;i<strlen(operand);i++)
		{
			if(operand[i]==',')
				break;
			index[i]=operand[i];	
		}
	}
	else
		strcpy(index,operand);
	
	
	while(1)
	{
		fscanf(fp3,"%s%s",label,addr);
		if(strcmp(index,label)==0)
			break;
	}
	
	fp4=fopen("optab.txt","r");
	while(1)
	{
		fscanf(fp4,"%s%s",mnemonic,code);
		if(strcmp(mnemonic,opcode)==0)
			break;
	}
	
	if(strstr(operand,",X"))
	{
		if(addr[0]=='0')
                               addr[0]='8';
                            else if(addr[0]=='1')
                               addr[0]='9';
                            else if(addr[0]=='2')
                               addr[0]='A';
                            else if(addr[0]=='3')
                               addr[0]='B';
                            else if(addr[0]=='4')
                               addr[0]='C';
                            else if(addr[0]=='5')
                               addr[0]='D';
                            else if(addr[0]=='6')
                               addr[0]='E';
                            else if(addr[0]=='7')
                               addr[0]='F';
		}
	
	fprintf(fp2,"%s\t%s\t%s\t%s\t%s-%s\n",add,label2,opcode,operand,code,addr);
	fscanf(fp1,"%s%s%s%s",add,label,opcode,operand);
}


while(strcmp(opcode,"END")!=0)
{
	fprintf(fp2,"%s\t%s\t%s\t%s\n",add,label,opcode,operand);
	fscanf(fp1,"%s%s%s%s",add,label,opcode,operand);
}

printf("Pass2ed.txt is created");

fclose(fp1);

fclose(fp2);

fclose(fp3);

fclose(fp4);

getch();

}
