#include "multitest.h"

double proc_min = 1;
double proc_max = -1;
double seq_min = 1;
double seq_max = -1;
double time_proc = 0;
double time_seq = 0;
double stD_proc = 0;
double stD_seq = 0;

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
    multi_process(list, val, size);
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

//Runs Sequential Search across Multiprocessing and Multithreading 
//Gets average time for 150 subarrays with each subarray containing 250 elements
//Averages run time for searches of every 50 elements that are less than the current size
void testCaseA(){
   for(int size = 250; size < 37500; size += 250){
   time_seq = 0;
   time_proc = 0;
   int * list = (int*)malloc(sizeof(int) * size);
   for(int i = 0; i < size; i++){
    list[i] = i+1;
    } // Fill the list 
    scramble_all(list, size);
    for(int i = 50; i < size; i += 50){
      time_proc += test_proc(list,i, size);
      time_seq += test_seq(list,i,size);
      scramble(list,size);
    }
      printf("Proc: %f, Seq %f\n", time_proc/size, time_seq/size);
      free(list);
    }
}

//Randomly Generates a Value to be searched, and searches MAX_SIZE of 37,500 elements 
//Gets the Average Run time for 150 subarrays with each subarray containing 250 elements
void testCaseB(){
   srand(time(NULL));
   for(int size = 250; size < 37500; size += 250){
   time_seq = 0;
   time_proc = 0;
   int * list = (int*)malloc(sizeof(int) * size);
   for(int i = 0; i < size; i++){
    list[i] = i+1;
    } // Fill the list 
    scramble_all(list, size);
    for(int x = 50; x < size; x += 50){
    int i = (rand() % (size-1))+1;
    time_proc += test_proc(list,i, size);
    time_seq += test_seq(list,i,size);
    scramble(list,size);
    }
    printf("Proc: %f, Seq %f\n", time_proc/size, time_seq/size);
    free(list);
    }
}
  


//Take in a size and a requested value 
//Values are 1 to size 
//MAX_SIZE = 250,000. There ulimit -u gives us 2000 processes. We limit it to 150 Max 250 values per 
//Process = size/250 + 1 if Remainder > 0
//Parent pid changes but we can determine child number by Child Pid - Parent Pid. 
//So Indexs are covered by 250*(Child Pid - Parnet Pid)

  //  stD_seq = sqrt(((time_seq*time_seq)/i) - ((time_seq/i) * (time_seq/i)));
  //stD_proc = sqrt(((time_proc * time_proc)/i) - ((time_proc/i) * (time_proc/i)));
int main(int argc, char** argv){

  testCaseB();
  
/*
  int size = atoi(argv[1]); 
  int * list = (int*)malloc(sizeof(int) * size);
  for(int i = 0; i < size; i++){
   list[i] = i+1;
  } // Fill the list 
  
  double time_proc = 0, time_seq = 0, stD_proc = 0, stD_seq = 0;
  scramble_all(list, size);
  for(int i = 0; i < size; i++){
    //Process
    time_proc += test_proc(list,size-i, size);
    stD_proc = sqrt(((time_proc * time_proc)/i) - ((time_proc/i) * (time_proc/i)));
    
    //Sequential
    time_seq += test_seq(list,size-i,size);
    stD_seq = sqrt(((time_seq*time_seq)/i) - ((time_seq/i) * (time_seq/i)));
    scramble(list,size);
  }

  */
  
  printf("The total time taken to find value in Process is: %f seconds\n", time_proc);     
  printf("The max proc is %f and the min proc is %f\n",proc_max, proc_min);
  printf("Average Proc time is %f\n", time_proc/100);
  printf("The Standard Deviation of Proc is %f\n", stD_proc);
 printf("The total time taken to find value in Sequential is: %f seconds\n", time_seq);  
  printf("Average Seq time is %f\n", time_seq/100);
  printf("The max is %f and the min is %f\n",seq_max, seq_min);
  printf("The Standard Deviation of Seq is %f\n", stD_seq);
  
}