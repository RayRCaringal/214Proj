#include "multitest.h"

void scramble(int list[], int size){
  srand(time(NULL));
  int first,  second;
  for(int i = 0; i < size/2; i++){
      first = (rand()%size)+1;
      second =(rand()%size)+1;
      list[first] = list[second];
  }
}


//Take in a size and a requested value 
//Values are 1 to size 
//MAX_SIZE = 250,000. There ulimit -u gives us 2000 processes. We limit it to 100 Max 250 values per 
//Process = size/250 + 1 if Remainder > 0
//Parent pid changes but we can determine child number by Child Pid - Parent Pid. 
//So Indexs are covered by 250*(Child Pid - Parnet Pid)
int main(int argc, char** argv){

  //printf("%d\n", getpid());
  int val = atoi(argv[1])-1;
  int size = atoi(argv[1]); 
  //printf("Size is %d\n", size);
  int * list = (int*)malloc(sizeof(int) * size);
  for(int i = 0; i < size; i++){
   list[i] = i+1;
  // printf("%d\n",list[i]);
  } // Fill the list 
  
  
  int pid, processes;
  int pids[size/250];
  //When 250 creates 1 child process, when 251 creates 2 child processes
  if(size < 250){
    processes = 1;
  }else if(size%250 > 0){
    processes = (size/250)+1; 
  }else{
    processes = size/250; 
  }
  //printf("Processes: %d\n", processes);
  for (int i = 0; i < processes; i++){
    pid = fork();
    if (pid < 0) {
      printf("Fork failed\n");
    }else if (pid == 0) { // Child Process 
      search(size, list, val,i);  
    //  printf("Child is %d\n",i);
      exit(0);
    }else{ //Parent Process, stores the pids
      pids[i] = pid;
    }
  }
  
 // printf("Process = %d\n",processes);
  int value,return_val;
  for(int i = 0; i < processes; i++){
    waitpid(pids[i], &value,WUNTRACED);
    if(WEXITSTATUS(value) > 0){ //Gets the return value
      return_val = (250*i)+WEXITSTATUS(value);  
    }else if(i == processes-1){ //If on the last child, and the return value == 0 then it must be the last index
      return_val = (250*i)-1;  
    }
    
  }
      printf("Index of %d: %d\n",val, return_val);
       
       free(list);
  
  
  
}