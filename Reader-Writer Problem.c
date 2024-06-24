#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Shared data
int shared_data = 0;

// Reader-Writer synchronization
pthread_mutex_t rw_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int read_count = 0;

// Reader function
void* reader(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        pthread_mutex_lock(&rw_mutex);
    }
    pthread_mutex_unlock(&mutex);

    // Reading section
    printf("Reader %d: read shared_data = %d\n", id, shared_data);
    sleep(1); // Simulate reading time

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        pthread_mutex_unlock(&rw_mutex);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Writer function
void* writer(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&rw_mutex);

    // Writing section
    shared_data++;
    printf("Writer %d: wrote shared_data = %d\n", id, shared_data);
    sleep(1); // Simulate writing time

    pthread_mutex_unlock(&rw_mutex);

    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    int reader_ids[5], writer_ids[2];

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0) {
            perror("Failed to create reader thread");
            exit(1);
        }
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0) {
            perror("Failed to create writer thread");
            exit(1);
        }
    }

    // Join reader threads
    for (int i = 0; i < 5; i++) {
        if (pthread_join(readers[i], NULL) != 0) {
            perror("Failed to join reader thread");
            exit(1);
        }
    }

    // Join writer threads
    for (int i = 0; i < 2; i++) {
        if (pthread_join(writers[i], NULL) != 0) {
            perror("Failed to join writer thread");
            exit(1);
        }
    }

    return 0;
}
