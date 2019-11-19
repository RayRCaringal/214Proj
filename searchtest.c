#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h> 

//For Processes
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void scramble(int list[], int size){
  srand(time(NULL));
  int first,  second;
  for(int i = 0; i < size/2; i++){
      first = (rand()%size)+1;
      second =(rand()%size)+1;
      list[first] = list[second];
  }
}

//Search Function returns an index between 0-249, in a subarray of 250 or less
void search(int size, int *arr, int val, int child){
    int index;
    if(child < size/250){ //Search if the array size is 250
      index = (child+1) * 250; //Child starts at 0, but it's the first child. We determine size by multilying by 250
      for (int i = index-250; i < index; i++) { //Index is the Cap
          if (arr[i] == val){
            if(i%250 == 0){ //i is the actual index, but exit only returns 8bits, so we send an index between 0-249
              exit(250);
            }else{
              exit(i%250);
            }
            break;
          } 
        }      
    }else{ // Search if array size is less than 250
      index = size%250;   
     // printf("Index is %d\n",index);
     //  printf("Size is %d\n",size);
     //  printf("Size-Index is %d\n",size-index);
      for(int i = (size-index); i < size; i++){  
         if (arr[i] == val){
         //   printf("I %d\n",i);
            exit(i%250);
            break;
          } 
        }
      } 
  return;
    }


//Take in a size and a requested value 
//Values are 1 to size 
//MAX_SIZE = 100,000. There ulimit -u gives us 2000 processes. We limit it to 400 Max 250 values per 
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
  
  printf("Process = %d\n",processes);
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