
#include<stdio.h>
#include<conio.h>
#include<string.h>
struct one_pass
{
	int addr,flag;
	char label[10],opcode[10],operand[10],oc[10],symbl[10];
}b[100];
int n=0;

int main()
{
	FILE *fp1,*fp2,*fp3,*fp4,*fp5;
	int locctr=0,start=0,fref[10],i=0,j;
	
	fp1=fopen("Input.txt","r");
	fp3=fopen("symbol.txt","w");
	fscanf(fp1,"%s%s%s",b[n].label,b[n].opcode,b[n].operand);
	
	if(strcmp(b[n].opcode,"START")==0)
	{
		locctr=atoi(b[n].operand);
		start=locctr;
		++n;
		fscanf(fp1,"%s%s%s",b[n].label,b[n].opcode,b[n].operand);
	}
	
	while(strcmp(b[n].opcode,"END")!=0)
	{
		b[n].addr=locctr;
		b[n].flag=0;
		if(strcmp(b[n].label,"**")!=0)
		{
			fprintf(fp3,"%s %d\n",b[n].label,locctr);
			if(strcmp(b[n].opcode,"RESW")==0)
			{
				locctr+=(3*atoi(b[n].operand));
			}
			else if(strcmp(b[n].opcode,"WORD")==0)
			{
				locctr+=3;
			}
			else if(strcmp(b[n].opcode,"RESB")==0)
			{
				locctr+=(atoi(b[n].operand));
			}
			else if(strcmp(b[n].opcode,"BYTE")==0)
			{
				locctr+=(strlen(b[n].operand)-3);
			}
		}
		if((strcmp(b[n].opcode,"RESW")!=0)&&(strcmp(b[n].opcode,"RESB")!=0)&&(strcmp(b[n].opcode,"WORD")!=0)&&(strcmp(b[n].opcode,"BYTE")!=0))
		{
				//opcode
				locctr+=3;
				fp2=fopen("optab.txt","r");
				char opc[10],opv[10];
				fscanf(fp2,"%s%s",opc,opv);
				while(strcmp(opc,"END")!=0)
				{
					if(strcmp(b[n].opcode,opc)==0)
					{
						strcpy(b[n].oc,opv);
						break;
					}
					fscanf(fp2,"%s%s",opc,opv);
				}
				b[n].flag=1;	
		}
		++n;
		fscanf(fp1,"%s%s%s",b[n].label,b[n].opcode,b[n].operand);
	}
	fprintf(fp3,"END **");
	fclose(fp3);
	//input symbols
	fp5=fopen("output.txt","w");
	for(j=0;j<n;++j)
	{
		if(b[j].flag==1)
		{
			fp4=fopen("symbol.txt","r");
			char syc[10],syv[10];
			fscanf(fp4,"%s%s",syc,syv);
			while(strcmp(syc,"END")!=0)
			{
					if(strcmp(b[j].operand,syc)==0)
					{
						strcpy(b[j].symbl,syv);
						break;
					}
					fscanf(fp4,"%s%s",syc,syv);
			}
		}
		printf("%d\t%s\t%s\t%s\t%s%s\n",b[j].addr,b[j].label,b[j].opcode,b[j].operand,b[j].oc,b[j].symbl);
		fprintf(fp5,"%d\t%s\t%s\t%s\t%s%s\n",b[j].addr,b[j].label,b[j].opcode,b[j].operand,b[j].oc,b[j].symbl);
	}
	getch();
	return 0;
}
