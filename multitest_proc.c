#include "multitest.h"

//Search Function returns an index between 0-249, in a subarray of 250 or less
int search(int size, int *arr, int val, int child){
    int index;
    if(child < size/250){ //Search if the array size is 250
      index = (child+1) * 250; //Child starts at 0, but it's the first child. We determine size by multilying by 250
      for (int i = index-250; i < index; i++) { //Index is the Cap
          if (arr[i] == val){
            if(i%250 == 0){ //i is the actual index, but exit only returns 8bits, so we send an index between 0-249
              return 250;
            }else{
              return i%250;
            }
          } 
        }      
    }else{ // Search if array size is less than 250
      index = size%250;   
      for(int i = (size-index); i < size; i++){  
         if (arr[i] == val){
            return i%250;
          } 
        }
      } 
  return 0;
    }


void multi_process(int *list, int val, int size){
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
  for (int i = 0; i < processes; i++){
    pid = fork();
    if (pid < 0) {
      printf("Fork failed\n");
    }else if (pid == 0) { // Child Process 
      exit(search(size, list, val,i));
    }else{ //Parent Process, stores the pids
      pids[i] = pid;
    }
  }
  
  int value;
 // int return_val;
  for(int i = 0; i < processes; i++){
    waitpid(pids[i], &value,WUNTRACED);
    if(WEXITSTATUS(value) > 0){ //Gets the return value
    //  return_val = (250*i)+WEXITSTATUS(value);  
    }else if(i == processes-1){ //If on the last child, and the return value == 0 then it must be the last index
   //   return_val = (250*i)-1;  
    }   
  }
   //   printf("Index of %d: %d\n",val, return_val);
 
  
  
}

