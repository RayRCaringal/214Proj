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
  
  multi_process(list, val, size);
        
       free(list);
  
  
  
}