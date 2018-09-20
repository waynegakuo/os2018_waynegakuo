#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//start of the function
int main(int argc, char *argv[]) {
        char ch [1024];
        FILE *file;
        int i;


        //looping through the user's input or arguments
        for (i=2; i<argc; i++){
                file=fopen(argv[i], "r"); //reading from file
                if (file== NULL) //if the file not found
                {
                        perror("Error opening file. \n");
                        exit (EXIT_FAILURE);
                }
                while(fgets(ch, sizeof(ch), file) !=NULL){
                        if (strstr(ch, argv[1]))
                                printf("%s", ch);
                }
                fclose(file); //close file
        }
}

