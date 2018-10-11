#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 32

int main(int argc, char *argv[]){
	char *line;  //get command line
    	char* comm[1024];        //user command
    	char* path= "/bin/";    //set path at bin
    	char progpath[20];      //full file path
    	int count;               //arg count
	size_t buffsize=32;
	size_t characters;
	char *com[1024];


	void rem_newline(char *line){
		int new_ln=strlen(line)-1;
		if (line[new_ln]== '\n')
			line[new_ln]='\0';
	}
	if (argc==1){

	while(1){

    		printf("wish> ");
		line=(char *)malloc(buffsize * sizeof(char));
		getline(&line, &buffsize, stdin);
		rem_newline(line);

		char *token;
                int argc; //taking argument count
                token= strtok(line, " ");
                int i=0;
                char **argv= malloc (100 * sizeof(char*)); //storing tokens into array of pointers of pointers
                while (token!=NULL){
                        comm[i]=token;
                        token=strtok(NULL, " ");
                        i++;
                }
                //argv[i]=NULL;
                count=i;



		printf("Round two: %s\n", comm[0]);
 		if (strcmp(comm[0], "exit")==0){
			exit(0);
		}

		else if (strcmp(comm[0], "cd")==0){
			if(chdir(comm[1])==-1)
				printf("Please provide directory to move into \n");
			else
				printf("succeeded \n");
		}


		else if (strcmp(comm[0], "ls")==0) {
			printf ("here here");
			char *arr[10]; //array for execv
			for (int i=1; i<11; i++){
				arr[i]=NULL;
			}
			if (count>1){
				for (int x=1; x<count; x++){
					arr[x]=comm[x];
					}
			}
			printf("%s", comm[0]);

			char *path1=strcat("/usr/bin/", comm[0]);
			char *path2=strcat("/bin/", comm[0]);

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
	else if(argc==2){
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

	while(getline(&line, &buffsize,fp) !=-1){
                rem_newline(line);

		char *token;
                int argc; //taking argument count
                token= strtok(line, " ");
                int i=0;
                char **argv= malloc (100 * sizeof(char*)); //storing tokens into array of pointers of pointers
                while (token!=NULL){
                        comm[i]=token;
                        token=strtok(NULL, " ");
                        i++;
                }
                //argv[i]=NULL;
                count=i;

                printf("Round two: %s\n", comm[0]);
                if (strcmp(comm[0], "exit")==0){
                        exit(0);
                }

                else if (strcmp(comm[0], "cd")==0){
                        if(chdir(comm[1])==-1)
                                printf("Please provide directory to move into \n");
                        else
                                printf("succeeded \n");
                }
                //for (i=0; i<argc; i++){
                //      printf("%s\n", argv[i]);
                //}

                else if (strcmp(comm[0], "ls")==0) {
                        printf ("here here");
                        char *arr[10]; //array for execv
                        for (int i=1; i<11; i++){
                                arr[i]=NULL;
                        }
                        if (count>1){
                                for (int x=1; x<count; x++){
                                        arr[x]=comm[x];
                                        }
                        }
                        printf("%s", comm[0]);

                        char *path1=strcat("/usr/bin/", comm[0]);
                        char *path2=strcat("/bin/", comm[0]);
                        //com["/usr"]
 //printf("%s", argv[0]);
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
fclose(fp);
}

	//batch mode
//printf("batch mode \n");

}


