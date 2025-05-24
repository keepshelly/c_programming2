#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TASK 6

#if TASK == 1
void* thread_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Child thread: line %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    
    for (int i = 0; i < 5; i++) {
        printf("Main thread: line %d\n", i);
    }
    
    pthread_join(thread, NULL);
    return 0;
}

#elif TASK == 2
//ожидание
void* thread_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Child thread: line %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    
    pthread_join(thread, NULL);
    
    for (int i = 0; i < 5; i++) {
        printf("Main thread: line %d\n", i);
    }
    
    return 0;
}

#elif TASK == 3
//параметры
void* thread_func(void* arg) {
    char* message = (char*)arg;
    for (int i = 0; i < 5; i++) {
        printf("%s: line %d\n", message, i);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    char* messages[] = {
        "Thread 1",
        "Thread 2",
        "Thread 3",
        "Thread 4"
    };
    
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, messages[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}

#elif TASK == 4
//заверш нити без ожидания
void* thread_func(void* arg) {
    char* message = (char*)arg;
    for (int i = 0; i < 5; i++) {
        printf("%s: line %d\n", message, i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    char* messages[] = {
        "Thread 1",
        "Thread 2",
        "Thread 3",
        "Thread 4"
    };
    
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, messages[i]);
    }
    
    sleep(2);
    
    for (int i = 0; i < 4; i++) {
        pthread_cancel(threads[i]);
    }
    
    return 0;
}

#elif TASK == 5
//обработать заверш потока
void cleanup_handler(void* arg) {
    printf("Cleaning up: %s\n", (char*)arg);
}

void* thread_func(void* arg) {
    char* message = (char*)arg;
    pthread_cleanup_push(cleanup_handler, message);
    
    for (int i = 0; i < 5; i++) {
        printf("%s: line %d\n", message, i);
        sleep(1);
    }
    
    pthread_cleanup_pop(0);
    return NULL;
}

int main() {
    pthread_t threads[4];
    char* messages[] = {
        "Thread 1",
        "Thread 2",
        "Thread 3",
        "Thread 4"
    };
    
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, messages[i]);
    }
    
    sleep(2);
    
    for (int i = 0; i < 4; i++) {
        pthread_cancel(threads[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}

#elif TASK == 6
//слипсорт
void* sleep_sort(void* arg) {
    int value = *(int*)arg;
    sleep(value);
    printf("%d ", value);
    return NULL;
}

int main() {
    int arr[] = {3, 1, 4, 2, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    pthread_t threads[n];
    
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, sleep_sort, &arr[i]);
    }
    
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\n");
    return 0;
}

#else
#error "Please define TASK between 1 and 6"
#endif