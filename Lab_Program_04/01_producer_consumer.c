// Producer consumer problem using semaphores

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;           // counts empty slots
sem_t full;            // counts filled slots
pthread_mutex_t mutex; // for mutual exclusion

// Producer function
void *producer(void *arg) {
  int item, i = 0;

  while (1) {
    item = i++; // produce an item

    sem_wait(&empty);           // wait for empty slot
    pthread_mutex_lock(&mutex); // enter critical section

    buffer[in] = item;
    printf("Produced: %d at buffer[%d]\n", item, in);

    in = (in + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex); // leave critical section
    sem_post(&full);              // signal item available

    sleep(1); // simulate production time
  }
}

// Consumer function
void *consumer(void *arg) {
  int item;

  while (1) {
    sem_wait(&full);            // wait for filled slot
    pthread_mutex_lock(&mutex); // enter critical section

    item = buffer[out];
    printf("Consumed: %d from buffer[%d]\n", item, out);

    out = (out + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex); // leave critical section
    sem_post(&empty);             // signal empty slot

    sleep(2); // simulate consumption time
  }
}

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  pthread_t prod, cons;

  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&prod, NULL, producer, NULL);
  pthread_create(&cons, NULL, consumer, NULL);

  pthread_join(prod, NULL);
  pthread_join(cons, NULL);

  sem_destroy(&empty);
  sem_destroy(&full);
  pthread_mutex_destroy(&mutex);

  return 0;
}
