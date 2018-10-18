/*
 * Author: Severin Deng, Brian Guth
 * Purpose: Create three Queues and four threads
 *          to do the conversion of input
 * Language:  C
 */
 
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#define q_size  10;

Queue *q1, *q2, *q3;
pthread_t reader, munch1, munch2, writer;

int main() {
  q1 = CreateStringQueue(q_size);
  q2 = CreateStringQueue(q_size);
  q3 = CreateStringQueue(q_size);
    
  int pthread_create(&reader, NULL, reader_start, NULL);  
    
    
    
  return 1;  // successfully xxx
}


void *reader_start(void *arg) {
  
  while () {
    



  }  
    
    
    
}