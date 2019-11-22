#include "multitest.h"

double proc_min = 1;
double proc_max = -1;
double seq_min = 1;
double seq_max = -1;

//Scrambles everything, only use at beginning
void scramble_all(int *list, int size){
  srand(time(NULL));
  int first,  second;
  for(int i = 0; i < size/2; i++){
      first = (rand()%(size-1))+1;
      second = (rand()%(size-1))+1;
      int temp = list[first];
      list[first] = list[second];
      list[second] = temp;
  }
}

//Scrambles once, use after the beginning
void scramble(int *list, int size){
  srand(time(NULL));
  int first,  second;
  first = (rand()%(size-1))+1;
  second = (rand()%(size-1))+1;
  int temp = list[first];
  list[first] = list[second];
  list[second] = temp;
  
}

//Times Multiprocessing 
 double test_proc(int *list, int val, int size){
    struct timeval begin, end;
    double elapsed;
    gettimeofday(&begin, NULL);
    multi_process(list, 123, size);
    gettimeofday(&end, NULL);
    elapsed = (double) (end.tv_sec - begin.tv_sec) + (double) ((end.tv_usec - begin.tv_usec)/1000000.0);
    if(elapsed < proc_min){
      proc_min = elapsed;
    }else if(elapsed > proc_max){
      proc_max = elapsed;
    }
    return elapsed;
}

//Times sequential search 
double test_seq(int *list, int val, int size){
     struct timeval begin, end;
    double elapsed;
    gettimeofday(&begin, NULL);
    for(int i = 0; i < size; i++){
      if(list[i] == val){
      //  printf("Index of %d: %d\n", i, val);
      }
    }
    gettimeofday(&end, NULL);
    elapsed = (double) (end.tv_sec - begin.tv_sec) + (double) ((end.tv_usec - begin.tv_usec)/1000000.0);
    if(elapsed < seq_min){
      seq_min = elapsed;
    }else if(elapsed > seq_max){
      seq_max = elapsed;
    }
    return elapsed;
}

//Take in a size and a requested value 
//Values are 1 to size 
//MAX_SIZE = 250,000. There ulimit -u gives us 2000 processes. We limit it to 100 Max 250 values per 
//Process = size/250 + 1 if Remainder > 0
//Parent pid changes but we can determine child number by Child Pid - Parent Pid. 
//So Indexs are covered by 250*(Child Pid - Parnet Pid)
int main(int argc, char** argv){


  int size = atoi(argv[1]); 
  int * list = (int*)malloc(sizeof(int) * size);
  for(int i = 0; i < size; i++){
   list[i] = i+1;
  } // Fill the list 
  
  double time_proc = 0, time_seq = 0, stD_proc = 0, stD_seq = 0;
  scramble_all(list, size);
  for(int i = 0; i < 100; i++){
    //Process
    time_proc += test_proc(list,size-i, size);
    stD_proc = sqrt(((time_proc * time_proc)/i) - ((time_proc/i) * (time_proc/i)));
    
    //Sequential
    time_seq += test_seq(list,size-i,size);
    stD_seq = sqrt(((time_seq*time_seq)/i) - ((time_seq/i) * (time_seq/i)));
    scramble(list,size);
  }


  
  printf("The total time taken to find value in Process is: %f seconds\n", time_proc);     
  printf("The max proc is %f and the min proc is %f\n",proc_max, proc_min);
  printf("Average Proc time is %f\n", time_proc/100);
  printf("The Standard Deviation of Proc is %f\n", stD_proc);
  printf("The total time taken to find value in Sequential is: %f seconds\n", time_seq);  
  printf("Average Seq time is %f\n", time_seq/100);
  printf("The max is %f and the min is %f\n",seq_max, seq_min);
  printf("The Standard Deviation of Seq is %f\n", stD_seq);
  free(list);
  
  
  
}