#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 32

int main(){
	char *line;  //get command line
    	char* argv[100];        //user command
    	char* path= "/bin/";    //set path at bin
    	char progpath[20];      //full file path
    	int argc;               //arg count
	size_t buffsize=32;
	size_t characters;
	const char * exit_cmd="exit";
	while(1){

    		printf("wish> ");
		line=(char *)malloc(buffsize * sizeof(char));
		characters=getline(&line, &buffsize, stdin);
		printf("You typed: '%s'", line);
		//char y=line[0];
 		//if (strstr(const (line[0]), exit_cmd)==0){
		//	exit(0);
		//}


		char *token;
		int argc; //taking argument count
		token= strtok(line, " ");
		int i=0;
		char **argv= malloc (100 * sizeof(char*)); //storing tokens into array of pointers of pointers
		while (token!=NULL){
			argv[i]=token;
			token=strtok(NULL, " ");
			i++;
		}
		argv[i]=NULL;
		argc=i;

		for (i=0; i<argc; i++){
			if(strcmp(argv[i], "exit")==0){
				printf("Exit fam");
			}
			printf("%s\n", argv[i]);
		}

		pid_t pid, wpid;
		int status;

		pid=fork();
		if (pid=0){
			if (execv(argv[0], argv)==-1){
				perror("lsh");
			}
			exit(1);
		}
		else if (pid<0){
			perror("ls");
		}
		else {
			wait(NULL);
			printf("Child exited");
		}
		//printf("%s", argv);
		}

	}
