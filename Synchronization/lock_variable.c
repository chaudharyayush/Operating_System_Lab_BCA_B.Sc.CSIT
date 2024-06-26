#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int lock = 0; // Initialize lock variable to 0

void *thread_function(void *arg)
{
    // Entry section
    while (lock != 0);
    printf("Thread %d intialize the lock\n", *(int *)arg);

    //sleep(1);   // Busy-wait until the lock is released
    lock = 1; // Acquire the lock
    printf("Thread %d Acquire the lock\n", *(int *)arg);

    // Critical section
     printf("Thread %d is in the critical section\n", *(int *)arg);
    // Perform some task that requires exclusive access to a shared resource

    // Exit section
    lock = 0; // Release the lock
    printf("Thread %d has released the lock\n", *(int *)arg);
    return NULL;
}

int main()
{
    pthread_t threads[5];
    int thread_args[5];
    int i;

    // Create 5 threads
    for ( i = 0; i < 5; i++)
    {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
        
    }

    // Wait for all threads to complete
    for ( i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
        
    }

    return EXIT_SUCCESS;
}
