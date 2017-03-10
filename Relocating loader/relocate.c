#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct single{
	// code1 denotes the first half byte ; code2 is the 2nd ; location is the location of this obj code
	char code1,code2;
	char loc[100];
}s[100];

struct modify{
	// modification address
	char loc[100];
}m[100];

int main()
{
	char line[100],*lined;
	FILE *inp,*out;
	inp=fopen("relInp.txt","r");
	out=fopen("relOut.txt","w");
	
	
	int i=0,j,select,index;
	// print the file decorations
	fprintf(out,"\t");
	// print the file as we want
	for(i=0;i<16;i++)
	{
		char values[2];
		sprintf(values,"%d",i);
		if(i==4 || i==8 || i==12)
        	fprintf(out,"\t ");    
        if(i==10)
    		values[0]='A';
    	if(i==11)
    		values[0]='B';   	
		if(i==12)
			values[0]='C';
		if(i==13)
    		values[0]='D';
    	if(i==14)
    		values[0]='E';
        if(i==15)
        {
            values[0]='F';
    	}
		values[1]='\0';
		fprintf(out,"%s ",values);
	}
	fprintf(out,"\n");
	
	// scan the first line ; header record
	fscanf(inp,"%s",line);
	// if the length of the header record is not 8 ; checking the name of the program is fully defined or not
	if(strlen(line)!=8)
	{
		fscanf(inp,"%s",line);
		// skip 1st character ^[ADDR]
		lined=line+1;
	}
	else
	{
		// copy 6 characters from line starting indexed at 9
		strncpy(lined,&line[9],6);
	}
	// get the starting address
	int addr=atoi(lined);
	
	fscanf(inp,"%s",line);
	
	// convert the address integer to the string
	char location[100],str[15];
	itoa(addr,location,10);
	// convert the hexa addr to decimal
	int startHexed = (int)strtol(location, NULL, 16);
	// get the starting address
	int start=addr/10*10;
	fprintf(out,"%d \t",start);
	// printing x for 1st empty set of addresses from the starting address of the row till that of the program
	for(i=start;i<addr;i++)
	{
		fprintf(out,"x ");
		
		sprintf(str, "%d", i);
		if(str[3]=='3' || str[3]=='7' || str[3]=='B')
			fprintf(out,"\t ");
	}
	// for the structure which contains each row
	i=-1;
	while(line[0]!='M')
	{
		// skip T^ in this record
		select=2;
		while(select!=strlen(line))
		{
			i+=1;
			// get the half-bytes
			if(line[select]=='^')
				select++;
			// get 1st half byte
			s[i].code1=line[select];
			++select;
			if(line[select]=='^')
				select++;
			// get 2nd half byte
			s[i].code2=line[select];
			select++;
			// get the location of the row
			strcpy(s[i].loc,location);
			// get next location by hexa manipulation
			if(location[3]=='9')
				location[3]='A';
			else if(location[3]=='F')
			{
				location[3]='0';
				if(location[2]=='9')
					location[2]='A';
				else
					location[2]+=1;
			}
			else
				location[3]+=1;
		}
		fscanf(inp,"%s",line);
	}
	
	
	// getting the modification record in the structure
	j=-1;
	while(line[0]!='E')
	{
		// skip M^
		select=2;
		while(select<=strlen(line))
		{
			j++;
			// copy 4 characters from line indexing at select to the array in the structure
			strncpy(m[j].loc,&line[select],4);
			select+=5;
		}
		fscanf(inp,"%s",line);
	}
	
	// lineNo signifies the modification record counter
	int lineNo=0;
	for(j=0;j<=i;j++)
	{
		// compare to see if the current address is to be modified
		if(strcmp(m[lineNo].loc,s[j].loc)==0)
		{
			// get the 5 half bytes starting from the current add half byte
			sprintf(str,"%c%c%c%c%c",s[j].code2,s[j+1].code1,s[j+1].code2,s[j+2].code1,s[j+2].code2);
			str[5]='\0';
			
			// convert the current hexa to decimal for addition
			int objHexed = (int)strtol(str, NULL, 16);
			// add the current add to starting add and convert back to hexa
			int add=objHexed+startHexed;
			char ans[10];
			sprintf(ans,"%x",add);
			
			// modify the codes accordingly and convert characters to upper case
			s[j].code2=toupper(ans[0]);
			s[j+1].code1=toupper(ans[1]);
			s[j+1].code2=toupper(ans[2]);
			s[j+2].code1=toupper(ans[3]);
			s[j+2].code2=toupper(ans[4]);
			
			// next modification record
			lineNo++;
		}
		// print the 2 half bytes
		fprintf(out,"%c%c",s[j].code1,s[j].code2);
		// get last character from the location
		index=strlen(s[j].loc)-1;
		// printing the values accordingly
		if(s[j].loc[index]=='3' || s[j].loc[index]=='7' || s[j].loc[index]=='B')
          	fprintf(out,"\t ");
        // if F in last index means go to next row
		if(s[j].loc[index]=='F')
        {
        	// incrementing the starting address of the row
            fprintf(out,"\n");
    		strcpy(location,s[j].loc);
    		if(location[3]=='9')
				location[3]='A';
			else if(location[3]=='F')
			{
				location[3]='0';
				if(location[2]=='9')
					location[2]='A';
				else
					location[2]+=1;
			}
			else
				location[3]+=1;
			fprintf(out,"%s\t",location);        	
        }	
	}
	// get address of last object code + 1 for X
	index=strlen(s[i].loc)-1;
	s[i].loc[index]+=1;
	// get initial address of the row
	int num = (int)strtol(location, NULL, 16);
	// add 16 to get the ending address + 1
	int end=num+16;
	// convert the current starting address from where X should start to decimal
	start = (int)strtol(s[i].loc, NULL, 16);
	// get last character of location
	char st=s[i].loc[3];
	// printing trailing X
	for(i=start;i<end;i++)
	{
		fprintf(out,"x ");
		if(st=='3' || st=='7' || st=='B')
			fprintf(out,"\t ");
		if(st=='9')
			st='A';
		else
			st+=1;
	}
	
	printf("Check relOut.txt for the output");
	fclose(out);
	
	getch();
	return 0;
}
