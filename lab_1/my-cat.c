#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   char ch;
   FILE *fp;

   fp = fopen(argv[1], "r"); // opens up a file


   if (fp == NULL)
   {
      perror("Error while opening the file.\n");//error if file does not exist
      exit(EXIT_FAILURE);
   }

   printf("Printing Contents:\n"); 

   //prints content of file

   while((ch = fgetc(fp)) != EOF)
      printf("%c", ch);

   fclose(fp);
   return 0;
}

