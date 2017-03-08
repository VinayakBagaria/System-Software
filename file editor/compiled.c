#include <stdio.h>

int main()
{
 FILE *fp;
 char filename[100];
 char ch;
 int linecount, wordcount, charcount;

 // Initialize counter variables
 linecount = 0;
 wordcount = 0;
 charcount = 0;

  
    // Open file in read-only mode
   fp = fopen("program.txt","r");

   // If file opened successfully, then write the string to file
   if ( fp )
   {
	//Repeat until End Of File character is reached.	
	   while ((ch=getc(fp)) != EOF) {
	   	  // Increment character count if NOT new line or space
		    if (ch != '\n') { ++charcount; }
		  
		  // Increment word count if new line or space character
		   if (ch == ' ' || ch == '\n') { ++wordcount; }
		   
		  // Increment line count if new line character
		   if (ch == '\n') { ++linecount; }
		   


	   }

	   if (charcount > 0) {
		++linecount;
		++wordcount;
	   }
    }
   else
      {
         printf("Failed to open the file\n");
        }

    printf("Lines : %d \n", linecount);
    printf("Words : %d \n", wordcount);
    printf("Characters : %d \n", charcount);

getchar();
return(0);
}
