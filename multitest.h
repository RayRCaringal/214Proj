#ifndef MULTITEST_H
#define MULTITEST_H

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


void search(int, int *, int, int);
void scramble(int* , int);

#endif