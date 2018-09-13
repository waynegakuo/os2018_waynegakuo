#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
   char ch;
   FILE *fp;
 
   fp = fopen(argv[1], "r"); // read mode
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
 
   printf("Printing Contents:\n");
 
   while((ch = fgetc(fp)) != EOF)
      printf("%c", ch);
 
   fclose(fp);
   return 0;
}
