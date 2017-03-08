#include<stdio.h>
#include<conio.h>
#include<string.h>

int main()
{
	int start=0;
	FILE *inp,*out;
	inp=fopen("absolute_inp.txt","r");
	out=fopen("absOut.txt","w");
	
	int i=0;
	fprintf(out,"\t");
	// print the file as we want
	for(i=0;i<16;i++)
	{
		char values[2];
		sprintf(values,"%d",i);
		if(i==4)
        	fprintf(out,"\t ");    
        if(i==8)
    		fprintf(out,"\t ");
    	if(i==10)
    		values[0]='A';
    	if(i==11)
    		values[0]='B';   	
		if(i==12)
		{
			fprintf(out,"\t ");
			values[0]='C';
		}
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
	char line[100],line2[100];
	fscanf(inp,"%s",line);
	//printf("%s",line);
	char addr[10];
	if(line[0]=='H')
	{
		if(strlen(line)!=7)
		{
			// header record exists
			fscanf(inp,"%s",line);		
			
			for(i=1;i<strlen(line);i++)
			{
				addr[i-1]=line[i+1];
			}
		}
		else
		{
			for(i=7;i<strlen(line);i++)
			{
				addr[i-7]=line[i];
			}
		}
	}
	start=atoi(addr);
	fscanf(inp,"%s",line);
	addr[strlen(addr)-1]='0';
	int add=atoi(addr);
	fprintf(out,"%d\t",add);
	
	for(i=atoi(addr);i<start;i++)
	{
		fprintf(out,"x ");
		char section[10];
		char str[15];
		sprintf(str, "%d", i);
		if(str[3]=='3')
			fprintf(out,"\t ");
	}
	//start=atoi(addr);
	//fprintf(out,"\n");
	char init[4];
	sprintf(init,"%d",i);
	//fprintf(out,"%s\t",init);
	// got text record
	while(line[0]!='E')
	{
		char byte[2];
		int select=2;
		while(select!=strlen(line))
		{
			// check if limiter exists, then increase to select the next location
			if(line[select]=='^')
				select+=1;
			// get the first byte
			byte[0]=line[select];
			++select;
			if(line[select]=='^')
				select+=1;
			// get the 2nd byte
			byte[1]=line[select];
			// add a neccessary null character to define the end of string
			byte[2]='\0';
			++select;
			//printf("%s",byte);
			fprintf(out,"%s",byte);
			int index=strlen(init)-1;
		//	fprintf(out,"%s",byte);
			if(init[index]=='0')
                init[index]='1';
            else if(init[index]=='1')
                init[index]='2';
            else if(init[index]=='2')
                init[index]='3';
            else if(init[index]=='3')
            {
            	fprintf(out,"\t ");
            	init[index]='4';
			}
            else if(init[index]=='4')
            {
            	init[index]='5';
            	//fprintf(out,"\t ");
			}    
            else if(init[index]=='5')
                init[index]='6';
            else if(init[index]=='6')
                init[index]='7';
            else if(init[index]=='7')
            {
            	init[index]='8';
            	fprintf(out,"\t ");
			}
            else if(init[index]=='8')
            {
            	init[index]='9';
				//fprintf(out,"\t ");
			}
            else if(init[index]=='9')
                init[index]='A';
            else if(init[index]=='A')
                init[index]='B';
            else if(init[index]=='B')
            {
            	init[index]='C';
				fprintf(out,"\t ");
			}
            else if(init[index]=='C')
            {
            	init[index]='D';
			}    
            else if(init[index]=='D')
            {
            	init[index]='E';
            }
            else if(init[index]=='E')
            {
            	init[index]='F';
            }
                
            else if(init[index]=='F')
            {
            	init[index]=='G';
            	add+=10;
            	fprintf(out,"\n");
    			sprintf(init,"%d",add);
				fprintf(out,"%s\t",init);        	
            }
		}
		fscanf(inp,"%s",line);	
	}
	
	int extra=atoi(init);
	// extra x at the end of the loaded program
	for(i=extra;i<add+16;i++)
	{
		fprintf(out,"x ");
		if(i==add+3 || i==add+7 || i==add+11)
			fprintf(out,"\t ");
		
	}
	
	printf("Check absOut.txt for the output");
	// footer of program
	fclose(inp);
	// close output file
	fclose(out);
	getch();
	return 0;
}
