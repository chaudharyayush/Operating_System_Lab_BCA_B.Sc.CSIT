#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int lock = 0; // Initialize lock variable to 0

void *thread_function(void *arg)
{
    // Entry section

    
    //This is a built-in GCC (GNU Compiler Collection) atomic function.
    // It atomically sets the value of lock to 1 and returns the previous value of lock.
    //If lock was 0 (indicating that the lock was free), the function sets it to 1 (indicating that the lock is now acquired by the current thread) and returns 0.
    //If lock was already 1 (indicating that the lock was already acquired by another thread), the function leaves it as 1 and returns 1.
    while (__sync_lock_test_and_set(&lock, 1) == 1)
    {
        printf("Thread %d is waiting for the lock\n", *(int *)arg);
       
    }
   
    printf("Thread %d has acquired the lock\n", *(int *)arg);

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

    // Create 5 threads
    for (int i = 0; i < 5; i++)
    {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return EXIT_SUCCESS;
}
