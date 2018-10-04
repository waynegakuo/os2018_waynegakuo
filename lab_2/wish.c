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


	void rem_newline(char *line){
		int new_ln=strlen(line)-1;
		if (line[new_ln]== '\n')
			line[new_ln]='\0';
	}

	while(1){

    		printf("wish> ");
		line=(char *)malloc(buffsize * sizeof(char));
		//characters=
		getline(&line, &buffsize, stdin);
		//printf("You typed: %s", line);
		//char y=line[0];
		rem_newline(line);

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
                //argv[i]=NULL;
                argc=i;



		printf("Round two: %s\n", line);
 		if (strcmp(line, "exit")==0){
			exit(0);
		}


		else if (strcmp(argv[0], "cd")==0){
			if(chdir(argv[1])==-1)
				printf("failed");
			else
				printf("succeeded \n");
		}
		//for (i=0; i<argc; i++){
		//	printf("%s\n", argv[i]);
		//}



		else {
			char *arr[10]; //array for execv
			for (int i=1; i<11; i++){
				arr[i]=NULL;
			}
			if (argc>1){
				for (int x=1; x<argc; x++){
					arr[x]=argv[x];
					}
			}
			char *path1=strcat("/usr/bin/", argv[0]);
			char *path2=strcat("/bin/", argv[0]);

			

//			printf("%s", argv[0]);
			pid_t pid, wpid;
			int status;

			pid=fork();
			if (pid=0){
				if (access(path1, X_OK)==0){
					arr[0]=path1;
					execv(path1, arr);
				}
				else if(access(path2, X_OK)==0){
					arr[0]=path2;
					execv(path2, arr);
				}
			}
			else if (pid<0){
				perror("ls");
			}
			else {
				wait(NULL);
				printf("Child exited\n");
			}
		}
		//printf("%s", argv);
			}

		}
