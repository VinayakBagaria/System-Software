#include<stdio.h>
#include<conio.h>
#include<string.h>

void main()
{

char opcode[10],mnemonic[3],operand[10],label[10],code[10];

int locctr,start,length;

FILE *fp1,*fp2,*fp3,*fp4;

// contains input program
fp1=fopen("input.txt","r");
// will contain the symbol with their addresses
fp2=fopen("symtbl.txt","w");
// the output program with the assigned addresses
fp3=fopen("out.txt","w");
// stores the first line in the corresponding 3 arrays
fscanf(fp1,"%s%s%s",label,opcode,operand);
// if START exists in 1st line
if(strcmp(opcode,"START")==0)
{
// atoi(char *) converts the string argument to integer
start=atoi(operand);
// location counter initialisation
locctr=start;

fprintf(fp3,"\t%s\t%s\t%s\n",label,opcode,operand);

fscanf(fp1,"%s%s%s",label,opcode,operand);

}

else
// location is 0 as no start exists
locctr=0;
// till end instruction is not encountered
while(strcmp(opcode,"END")!=0)

{

fprintf(fp3,"%d\t",locctr);
// encountered a declarative statement
if(strcmp(label,"**")!=0)
fprintf(fp2,"%s\t%d\n",label,locctr);

fp4=fopen("optab.txt","r");
fscanf(fp4,"%s%s",code,mnemonic);
while(strcmp(code,"END")!=0)
{
if(strcmp(opcode,code)==0)
{
locctr+=3;
break;
}
fscanf(fp4,"%s%s",code,mnemonic);
}
fclose(fp4);


if(strcmp(opcode,"WORD")==0)

locctr+=3;

else if(strcmp(opcode,"RESW")==0)

locctr+=(3*(atoi(operand)));

else if(strcmp(opcode,"RESB")==0)

locctr+=(atoi(operand));

else if(strcmp(opcode,"BYTE")==0)

++locctr;

fprintf(fp3,"%s\t%s\t%s\t\n",label,opcode,operand);

fscanf(fp1,"%s%s%s",label,opcode,operand);

}

fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);

length=locctr-start;

printf("The length of the program is %d",length);

fclose(fp1);

fclose(fp2);

fclose(fp3);


getch();

}
