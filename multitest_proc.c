#include "multitest.h"

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

