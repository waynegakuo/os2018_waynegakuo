#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]) {
	char ch [1024];
	FILE *file;

	file=fopen(argv[2], "r"); //reading from file
	if (file== NULL)
	{
		perror("Error opening file. \n");
		exit (EXIT_FAILURE);
	}

	while(fgets(ch, sizeof(ch), file) !=NULL){
		if (strstr(ch, argv[1])!=NULL){
			printf("%s", ch);
	}
}

}

