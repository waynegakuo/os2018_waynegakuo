#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//declaring the functions for the builtin commands
int exit_cmd(char **args);
int cd_cmd(char **args);
//int path_cmd (char **args);

//a list containing the built in commands
char *builtin_cmds[]={
	"exit",
	"cd",
	//"path"
};

//functions of the commands corresponding to their names put in the list
int (*builtin_fn[])(char **)={
	&exit_cmd,
	&cd_cmd,
	//&path_cmd
};

int builtin_len(){
	return sizeof(builtin_cmds)/sizeof(char *);
}

//exit command
int exit_cmd(char **args){
	return 0;
}

//changing directory command
int cd_cmd(char **args){
	if (args[1]==NULL){
		fprintf(stderr, "kindly provide directory to \"cd\"\n");
	}
	else {
		if (chdir(args[1])!=0){
			perror("lsh");
		}
	}
	return 1;
}

int launch_shell (char **args){
	pid_t pid, wait_pid; //process ids
	int status;

	pid=fork();
	if (pid==0){ //child process
		if (execv(args[0], args)==-1){
			perror("execv failed");
		}
	exit(EXIT_FAILURE);

	}
	else if (pid>0){ //parent process
		if ((pid=wait(&status))<0){
			perror("wait");
			_exit(1);
		}
		printf("Parent: finished\n");
	}
	else {
		perror("fork failed");
	}
	return 0; //returns success
}

//executes program baased on builtin commands else launches the shell commands provided by user
int exec_prog(char **args){
	int i;
	if (args[0]==NULL){
		return 1; //empty command
	}

	for (i=0; i<builtin_len(); i++){
		if (strcmp(args[0], builtin_cmds[i])==0){
			return (*builtin_fn[i])(args);
		}
	}
	return launch_shell(args);
}

char *read_input(void){
	char *line =NULL;
	ssize_t buffsize=0;
        getline(&line, &buffsize, stdin);
	return line;
}
char **split_inputs(char *line){
	char *token;
        token= strtok(line, " ");
        int i=0;
	char* argc[100];

        while (token!=NULL){
		argc[i]=token;
                token=strtok(NULL, " ");
                i++;
        }
}

void start_process(void){
	char *line;
	char **args;
	int status;

	do{
		printf("wish> ");
		line=read_input();
		args=split_inputs(line);
		status=exec_prog(args);

		free(line);
		free (args);
	}
	while(status);
}

int main (int argc, char **argv){

	start_process();

	return EXIT_SUCCESS;
}

