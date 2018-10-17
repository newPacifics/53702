/*
 * Author: Severin Deng, Brian Guth
 * Purpose: Create a Queue module and structure for 
 *          synchronization
 * Language:  C
 */
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

const int BUFFER_SIZE = 1024;
pthread_mutex_t munch_1_mutex;
pthread_mutex_t munch_2_mutex;
pthread_mutex_t write_mutex;
pthread_cond_t munch1_cond;
pthread_cond_t munch2_cond;
pthread_cond_t w_cond;


/****************************************************************************
* Structure Name: Queue
*****************************************************************************
* This structure holds the array of char pointers, as well as some other 
* stats
*****************************************************************************/
typedef struct Queue {
  char **str_arr;
  int enqueueCount;
  int dequeueCount;
  int enqueueBlockCount;
  int dequeueBlockCount;
  int size;
  pthread_cond_t *condition;
  pthread_mutex_t *mutex;
  int lastIndex;
} Queue;

/****************************************************************************
* Function Name: CreateStringQueue
*****************************************************************************
* This function creates a new Queue of given size
*
* size: size of the queue to be made
* 
* Return a new Queue with size size
*****************************************************************************/
Queue * CreateStringQueue (int size) {
  Queue *q = malloc(sizeof(Queue) );
  if (q == NULL)
    fprintf(stdout, "%s\n", "Error allocating memory queue structure.");

  q->str_arr = (char **) malloc(sizeof(char*) * size);
  if (q->str_arr == NULL) {
    fprintf(stdout, "%s\n", "Error allocating memory to the string arry.");
  }
  
  q->enqueueCount = 0;
  q->dequeueCount = 0;
  q->enqueueBlockCount = 0;
  q->dequeueBlockCount = 0;
  q->size = size;
  q->lastIndex = 0;
  return q;
}

int mod_incr(int num, int mod) {
    return (++num) % mod;
}

void main() {
    mod_incr(19,20);
}
/****************************************************************************
* Function Name: CreateStringQueue
*****************************************************************************
* This function adds a new string to a given Queue
*
* q: The Queue to add the string to
* string: The string to be added
* 
* Does not return anything
*****************************************************************************/
void EnqueueString (Queue *q, char *string) {
  pthread_cond_t *condition = q->condition;
  pthread_mutex_t *mutex = q->mutex;
  while (q->lastIndex = q->size) {
    q->enqueueBlockCount++;
    pthread_cond_wait(condition, mutex);
  }
  pthread_mutex_lock(mutex);
  q->str_arr[q->lastIndex] = string;
  q->lastIndex++;
  if (q->lastIndex == 1) {
    pthread_cond_signal(condition);
  }
  pthread_mutex_unlock(mutex);
  return;
}

/****************************************************************************
* Function Name: DequeueString
*****************************************************************************
* This function dequeues a string from a given Queue
*
* q: The Queue to dequeue from
* 
* Returns the dequeue'd string
*****************************************************************************/
char * DequeueString (Queue *q) {
  char * s;
  pthread_mutex_t *mutex = q->mutex;
  while (q->lastIndex = 0) {
    q->dequeueBlockCount++;
    pthread_cond_wait(q->condition, mutex);
  }
  pthread_mutex_lock(mutex);
  s = q->str_arr[q->lastIndex];
  q->str_arr = NULL;
  q->lastIndex--;
  if (q->lastIndex == q->size - 1) {
    pthread_cond_signal(q->condition);
  }
  pthread_mutex_unlock(mutex);
  return s;
}

/****************************************************************************
* Function Name: PrintQueueStats
*****************************************************************************
* This function prints a given Queue's stats
*
* q: The Queue from which to print stats
* 
* Returns nothing
*****************************************************************************/
/*
void PrintQueueStats (Queue *q) {
  puts(q->enqueueCount);
  puts(q->dequeueCount);
  puts(q->enqueueBlockCount);
  puts(q->dequeueBlockCount);
  return;
}*/


