#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define BUFF_SIZE 32

size_t buffsize=32;
size_t characters;
pid_t pid, wpid;

char *progpath[20];      //full file path
int path_counter=2; //path counter initially set to 2
int path_active=0; //path active set to false

//removing new line character
void rem_newline(char *line){
  int ln=strlen(line)-1;
  if (line[ln]== '\n')
    line[ln]='\0';
}

//error message
void error_msg (){
  char error_message[30] = "An error has occurred\n";
  write(STDERR_FILENO, error_message, strlen(error_message));
}

//function used for concatination of commands
char* concat(const char *s1, const char *s2)
{
  const size_t len1 = strlen(s1);
  const size_t len2 = strlen(s2);
  char *result = malloc(len1 + len2 + 1);
  memcpy(result, s1, len1);
  memcpy(result + len1, s2, len2 + 1);
  return result;
}

//this function executes users commands
void *commandFunction(void *l){
  if (path_active==0){
    progpath[0]="/bin";
    progpath[1]= "usr/bin";

  }
  char *token; //split commands
  char *line= (char *)l;  //get command line
  char *comm[1024]; //user commands array

  rem_newline(line); //removes newline characters

  token= strtok(line, " "); //first token

  int i=0; //commands counter

  //adding tokens to commands array
  while (token!=NULL){
    comm[i]=token;
    token=strtok(NULL, " ");
    i++;
  }

  if (strcmp(comm[0], "path")==0){ //checks if 1st argument provided is 'path'
    path_counter=0;
    path_active=1;
    for (int m=1; m<i; m++){
      progpath[m-1]=malloc(strlen(comm[m])+1);
      strcpy(progpath[m-1], comm[m]);
      path_counter++;
    }
  }

  //exit function
  else if (strcmp(comm[0], "exit")==0){
    exit(0);
  }

  //changing directory
  else if (strcmp(comm[0], "cd")==0){
    if(chdir(comm[1])==-1)
      error_msg();
    else
      printf("Change directory successful \n");
  }

  else {

    char *arr[200]; //array for execv
    for (int k=1;k<10; k++){
      arr[k]=NULL;
    }

    int red= 0; //redirect check set to false
    char *fname; //filename
    if (i>1){
      for (int x=1; x<i; x++){
        if(strcmp(comm[x], ">")!=0){ //checks for redirection
          arr[x]=comm[x];
        }
        else{
          red = 1; //if found redirection set to true
          x++;
          fname = comm[x];
        }

      }
    }

    //start process
    pid=fork();
    if (pid==0){
      for (int j=0; j<path_counter; j++){
        char *path1=concat("/usr/bin/", comm[0]);
        char *path2=concat("/bin/", comm[0]);

        if (access(path1, X_OK)==0){
          arr[0]=path1;
          execv(path1, arr);
        }
        else if(access(path2, X_OK)==0){
          arr[0]=path2;

          if (red==1){
            FILE* file = fopen(fname, "w+");
            dup2(fileno(file), fileno(stdout));
            dup2(fileno(file), fileno(stderr));
            fclose(file);
          }
          execv(path2, arr);
        }
      }
      error_msg();
    }
    else {
      wait(NULL);
    }
  }
}

//main function
int main(int argc, char *argv[]){

  FILE *fp;
  char *line=NULL;  //get command line
  size_t buffsize=32;

  if (argc==1){


    while(1){
      printf("wish> ");
      line=(char *)malloc(buffsize * sizeof(char));
      getline(&line, &buffsize, stdin);

      rem_newline(line);

      //printf("Are we here yet?"); //confirm

      char *comm[10];//user commands array
      char *token; //split commands
      int count=0;

      token= strtok(line, "&");

      //char **argv= malloc (100 * sizeof(char*)); //storing tokens into array of pointers of pointers
      while (token!=NULL){
        comm[count]=token;
        token=strtok(NULL, "&");
        count++;
      }

      int l,m;
      pthread_t thread_new[count];

      for (l=0; l<count; l++){
        pthread_create(&thread_new[l], NULL, commandFunction, comm[l]);
      }

      for (m=0; m<count; m++){
        pthread_join(thread_new[m], NULL);
      }
    }
  }

  else if(argc==2){
    fp = fopen(argv[1], "r"); // opens up a file
    if (fp == NULL)
    {
      perror("Error while opening file.\n");//error if file does not exist
      exit(EXIT_FAILURE);
    }

    printf("Printing Contents:\n");

    //prints content of file

    while(getline(&line, &buffsize,fp) !=-1){
      rem_newline(line);

      char* comm[1024];//user commands array
      char *token; //split commands
      int count=0;

      token= strtok(line, "&");
      char **argv= malloc (100 * sizeof(char*)); //storing tokens into array of pointers of pointers
      while (token!=NULL){
        comm[count]=token;
        token=strtok(NULL, "&");
        count++;
      }
      //argv[i]=NULL;

      // printf("Round two: %s\n", comm[0]);
      int l,m;

      pthread_t thread_new_2[count];
      for (l=0; l<count; l++){
        pthread_create(&thread_new_2[l], NULL, commandFunction, comm[l]);
      }
      for (m=0; m<count; m++){
        pthread_join(thread_new_2[m], NULL);
      }
    }
  }
  else{
    printf("%s\n", "Two arguments allowed");
  }
  return 0;
}
