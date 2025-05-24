#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Выберите задачу (1-9)
#define TASK 9

#if TASK == 1 || TASK == 2 || TASK == 5 || TASK == 7
void* thread_func(void* arg) {
    #if TASK == 5
    pthread_cleanup_push((void(*)(void*))printf, "Child thread cleanup\n");
    #endif
    
    #if TASK == 7
    pthread_mutex_t* mutex = (pthread_mutex_t*)arg;
    #endif
    
    for (int i = 0; i < 5; i++) {
        #if TASK == 7
        pthread_mutex_lock(mutex);
        #endif
        
        printf("Child thread: line %d\n", i);
        
        #if TASK == 7
        pthread_mutex_unlock(mutex);
        #endif
        
        #if TASK == 4 || TASK == 5
        sleep(1);
        #endif
    }
    
    #if TASK == 5
    pthread_cleanup_pop(0);
    #endif
    
    return NULL;
}
#endif

int main() {
    #if TASK == 1 || TASK == 2
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    
    #if TASK == 1
    for (int i = 0; i < 5; i++) {
        printf("Main thread: line %d\n", i);
    }
    #endif
    
    pthread_join(thread, NULL);
    
    #if TASK == 2
    for (int i = 0; i < 5; i++) {
        printf("Main thread: line %d\n", i);
    }
    #endif
    #endif
    
    #if TASK == 3
    pthread_t threads[4];
    char* messages[] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4"};
    
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, messages[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    #endif
    
    #if TASK == 4 || TASK == 5
    pthread_t threads[4];
    char* messages[] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4"};
    
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, messages[i]);
    }
    
    sleep(2);
    
    for (int i = 0; i < 4; i++) {
        #if TASK == 4
        pthread_cancel(threads[i]);
        #else
        pthread_join(threads[i], NULL);
        #endif
    }
    #endif
    
    #if TASK == 6
    int arr[] = {3, 1, 4, 2, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    pthread_t threads[n];
    
    printf("Unsorted: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\nSorting...\n");
    
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, sleep_sort, &arr[i]);
    }
    
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\n");
    #endif
    
    #if TASK == 7
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_t thread;
    
    pthread_create(&thread, NULL, thread_func, &mutex);
    
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        printf("Main thread: line %d\n", i);
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_join(thread, NULL);
    pthread_mutex_destroy(&mutex);
    #endif
    
    #if TASK == 8 || TASK == 9
    int N = 4; // По умолчанию
    int threads = 2;
    
    #if TASK == 9
    // Тестируем разные размеры
    int sizes[] = {100, 500, 1000, 1500, 2000, 2500};
    int thread_counts[] = {1, 2, 4, 8, 16, 32, 64, 128};
    
    printf("Matrix Size,Threads,Time(ms)\n");
    
    for (int s = 0; s < sizeof(sizes)/sizeof(sizes[0]); s++) {
        for (int t = 0; t < sizeof(thread_counts)/sizeof(thread_counts[0]); t++) {
            N = sizes[s];
            threads = thread_counts[t];
    #endif
    
    int A[N][N], B[N][N], C[N][N];
    
    // Заполнение матриц
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = B[i][j] = 1;
        }
    }
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Распараллеливание
    pthread_t thread_ids[threads];
    ThreadData thread_data[threads];
    
    int rows_per_thread = N / threads;
    int remaining_rows = N % threads;
    
    for (int i = 0; i < threads; i++) {
        thread_data[i].N = N;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i + 1) * rows_per_thread;
    }
    
    if (remaining_rows > 0) {
        thread_data[threads-1].end_row += remaining_rows;
    }
    
    for (int i = 0; i < threads; i++) {
        pthread_create(&thread_ids[i], NULL, thread_multiply, &thread_data[i]);
    }
    
    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e3 + 
                       (end.tv_nsec - start.tv_nsec) / 1e6;
    
    #if TASK == 9
    printf("%d,%d,%.2f\n", N, threads, time_taken);
        }
    }
    #else
    printf("Time: %.2f ms\n", time_taken);
    
    if (N <= 5) {
        printf("Matrix A:\n");
        print_matrix(N, A);
        printf("Matrix B:\n");
        print_matrix(N, B);
        printf("Matrix C:\n");
        print_matrix(N, C);
    }
    #endif
    #endif
    
    return 0;
}

// Вспомогательные функции
#if TASK == 6
void* sleep_sort(void* arg) {
    int value = *(int*)arg;
    usleep(value * 10000);
    printf("%d ", value);
    return NULL;
}
#endif

#if TASK == 8 || TASK == 9
typedef struct {
    int N;
    int start_row;
    int end_row;
    int (*A)[];
    int (*B)[];
    int (*C)[];
} ThreadData;

void* thread_multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int (*A)[data->N] = data->A;
    int (*B)[data->N] = data->B;
    int (*C)[data->N] = data->C;
    
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < data->N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return NULL;
}

void print_matrix(int N, int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
#endif